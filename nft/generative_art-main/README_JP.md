このスクリプトは、レイヤーごとにランダムに抽出したIMGファイルを組み合わせた画像を大量生成するプログラムです。

## 完成版のサンプル
https://github.com/moyattodataman/generative_art/tree/main/output_sample

## レイヤーごとのリソースファイル
https://github.com/moyattodataman/generative_art/tree/main/components

## 手順

### 1. リポジトリをクローンしてください。

```
git clone https://github.com/moyattodataman/generative_art.git
```

### 2. リソースファイルの配置

1. レイヤーごとのリソースファイルを作成してください。
2. レイヤー別にディレクトリへ格納してください。
3. レイヤーが足りない場合は、追加作成してください。レイヤーが余る場合は、ディレクトリを削除してください。

```
ディレクトリ"1"; 一番下のレイヤー
ディレクトリ"2": 下から2番目のレイヤー
ディレクトリ"3": 下から3番目のレイヤー
以後同様
```

### 3. プログラムを起動してください。
完成ファイルが"output"ディレクトリに生成されます。

```
python generative_art/generate.py
```

## Udemyの講座も参考にしてください
https://www.udemy.com/course/generative-nft/?referralCode=3F804CAE2E1361EAE47A
[![Image from Gyazo](https://i.gyazo.com/e0919ba0bb9d18521c939ab8d0e38e25.png)](https://gyazo.com/e0919ba0bb9d18521c939ab8d0e38e25)
