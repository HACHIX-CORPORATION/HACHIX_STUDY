from transformers import pipeline
from sentence_transformers import SentenceTransformer
import faiss
import numpy as np
from read_novels import read_file_and_split_sentences

# 参照テキストのリスト
reference_texts = read_file_and_split_sentences(
	directory=r"D:\repos\study\HACHIX_STUDY\RAG\novels\novels")

print(f"len reference_texts = {len(reference_texts)}")

# モデルの初期化
embedding_model = SentenceTransformer('all-MiniLM-L6-v2')  # ベクトルエンコーディング用
qa_model = pipeline("question-answering")  # 質問応答モデル（Hugging Face Transformers）

# 参照テキストをベクトルにエンコード
reference_embeddings = embedding_model.encode(reference_texts)

# Faissインデックスの作成
index = faiss.IndexFlatL2(reference_embeddings.shape[1])
index.add(np.array(reference_embeddings))


def retrieve_relevant_texts(query, k=2):
	"""クエリに最も関連するテキストを取得"""
	query_embedding = embedding_model.encode([query])
	distances, indices = index.search(np.array(query_embedding), k)
	return [reference_texts[i] for i in indices[0]]


def answer_question_with_rag(question):
	"""質問に対するRAGの回答を生成"""
	# 参照テキストの取得
	relevant_texts = retrieve_relevant_texts(question)
	print(f"relevant_texts = {relevant_texts}")
	context = " ".join(relevant_texts)

	# 質問応答モデルで回答を生成
	result = qa_model(question=question, context=context)
	return result['answer']


# テスト
question = "骸骨男の正体は誰ですか？作中で言及されている氏名で答えること。"
answer = answer_question_with_rag(question)
print(f"Question: {question}")
print(f"Answer: {answer}")