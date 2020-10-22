# Campaign Web構築
1. システム概要
    - 一ヶ月限定で利用する
    - アクセス数は多くない

2. ステップ
    1. Region選択

    2. VPC構築

    3. EC2作成
        - グローバルIPアドレスの自動割当を無効にする。
        - 削除保護にチェックを入れる。
        - セキュリティグループの設定
            - ssh: IPを制限
            - http, https: すべてIPを許可

    4. 固定IPを設定する
        - Elastic IP

    5. DNS設定
        - Route53: (reference to port53)

3. キーワード
    1. FQDN: fully qualified domain name

4. サンプル構成図
    1. Patterns\CampaignWeb.drawio