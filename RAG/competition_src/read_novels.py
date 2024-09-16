import os

# 初回のみ必要: NLTKのpunktデータセットをダウンロード


def read_file_and_split_sentences(directory):
	"""指定されたファイルを読み取り、文ごとにリストに追加します"""
	sentences = ""

	# ファイルを読み取る
	for file_path in get_all_file_paths(directory):
		print(f"processing {file_path}")
		with open(file_path, 'r', encoding='shift-jis') as file:
			text = file.read()

			# テキストを文に分割
			sentences += text

	return sentences


def get_all_file_paths(directory):
	"""指定されたディレクトリ内のすべてのファイルパスをリストに取得"""
	file_paths = []

	# ディレクトリを再帰的に探索
	for root, dirs, files in os.walk(directory):
		for file in files:
			# ファイルのフルパスを取得
			full_path = os.path.join(root, file)
			file_paths.append(full_path)

	return file_paths
