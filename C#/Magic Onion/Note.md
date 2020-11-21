# magic onionとは
1. MagicOnionとは
    - Http/2を使用したgoogle製rpcフレームワーク「grpc」
    - C#で使いやすくラップし、
    - Unityでの動作もサポートしているリアルタイム通信が可能なフレームワークです。
    - サーバーサイドC#, クライアントとコード共有可能
        - サーバー側: .Net Core
        - クライント側：unity / .Net Core
    - https://www.slideshare.net/torisoup/magiconion-174973732
    
2. HTTP2とは
    - ストリームという概念を導入した。一つのコネクション内で同時に並行して複数の
    リクエスト、レスポンスを処理できるようにする。
    
3. RPCフレームワークとは
    - RPC (remote protocol Call)
        - プログラムから別のアドレス空間（通常、共有ネットワーク上の別のコンピュータ上）
    にあるサブルーチンや手続きを実行することを可能にする技術。
        - いわゆる「クライアント−サーバー」型の通信プロトコルであり、
        サーバー上で実装されている関数（Procedure、プロシージャ）
        をクライアントからの呼び出しに応じて実行する技術だ
        - 課題：
            - 基本的にテキストベースで情報をやり取りするためデータの転送効率が悪く、またバイナリデータを扱いにくいという問題があった。
            - HTTP/HTTPSを使用しているため比較的長い期間で散発的にデータをやり取りしにくかったり、転送効率の面でもオーバーヘッドが存在したりする
    - grpc: Googleが自社サービス向けに開発して使用していたものをオープンソース
        - Protocol Buffersを利用して高速かつ低用量での通信を実現
            - 言語やプラットフォームに依存しない、構造化されたデータをシリアライズする
            拡張可能なメカニズム。
            - XMLやJSONのようなIDL( Interface Definition Language)  
            - .protoという拡張子のファイルで定義
        - 参考
            - https://www.slideshare.net/KenjiroKubota/grpc-141520916
            - https://knowledge.sakura.ad.jp/24059/
            
4. Unityとは
    - ユニティ・テクノロジーズが開発しているゲームエンジンのことです。
    - 様々なプラットフォームでゲームを作れる！
    - 2D,3Dどちらでも作れる！
    
5. C++ アプリ　- C# Serverの連携

6. CLR とは
    - Common Language RunTime

7. COM
    - Component Object Model
    
8. GUIDとは
    - Global Unique Identifier
    


        
    
    
    

    
    