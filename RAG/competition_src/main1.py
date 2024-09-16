import numpy as np
from read_novels import read_file_and_split_sentences
from langchain.text_splitter import CharacterTextSplitter
from langchain.embeddings.openai import OpenAIEmbeddings
from langchain.vectorstores import Chroma
from langchain.chains import RetrievalQA
from langchain.chat_models import ChatOpenAI
import pandas as pd
import csv

#
text_splitter = CharacterTextSplitter(
    separator="。",
    chunk_size=200,
    chunk_overlap=50
    )

# 参照テキストのリスト
reference_texts = read_file_and_split_sentences(
	directory=r"D:\repos\study\HACHIX_STUDY\RAG\novels\novels")

docs = text_splitter.split_text(reference_texts)

embeddings = OpenAIEmbeddings(api_key="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")

db = Chroma.from_texts(docs, embeddings)
retriever = db.as_retriever()

chat = ChatOpenAI(
	model="gpt-4o",
	temperature=0,
	api_key="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"
)

qa_chain = RetrievalQA.from_chain_type(
    llm=chat,
    chain_type="stuff",
    retriever=retriever
)


def answer_question_with_rag(question):
	"""質問に対するRAGの回答を生成"""
	# 参照テキストの取得
	context_docs = retriever.get_relevant_documents(question)

	if context_docs:
		# 最初のドキュメントを最も関連性が高いとみなす
		most_relevant_document = context_docs[0]
		# ドキュメントからテキストを取得
		most_relevant_text = most_relevant_document.page_content
		print("Most relevant text:", most_relevant_text)
	else:
		most_relevant_text = "問題に関連する情報が見つかりませんでした"

	result = qa_chain.chat(question, context=most_relevant_document['text'])

	return most_relevant_text, result


def main(query_path):
	df = pd.read_csv(query_path)
	result_all = []
	for i, problem in enumerate(df["problem"]):
		ref, result = answer_question_with_rag(problem)

		result = [i + 1, result, ref]

		result_all.append(result)

	# CSVファイルのパス
	csv_file_path = './predictions.csv'

	# CSVファイルへの書き込み
	with open(csv_file_path, mode='w', newline='') as file:
		writer = csv.writer(file)
		writer.writerows(result_all)


csv_file_path = r'D:\repos\study\HACHIX_STUDY\RAG\competition_src\query1.csv'
main(csv_file_path)


