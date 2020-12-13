1. Import   
    - 関数までimportするのは良くない
    - ..はおすすめしない
    - import *を避けた方が良い
    
2. setup.pyでパッケージ化して配布する。
    - Tools -> create setup.py
    - Tools -> run setup.py
    
3. 標準ライブラリと組み込み関数のリストを活用
    - Ex: dict.setdefault()
    
4. デストラクタは __del__を利用する。

5. @property, setter

6. 抽象クラス abc.abstractmethod

7. 特殊メソッド
    - __eq__
    - __str__
    
8. ファイル操作とシステム
    - 読み込み
        - 1行ずつ
        - 指定文字ずつ読み込み
    - 読み込み位置を移動する
        - seek
    - Templateの機能がある
    
    - csvファイル
        - import csv
        
    - ライブラリ
        - pathlib
        - glob
        - shutil
    
    - ファイル圧縮
        - tarfile
        - zipfile
        - tempfile
    - コマンド実行
        - subprocess
        
9. コードスタイル
    - flake8
    - 
        
        

    


