#C++の規格
1. C++11, C++14, C++17 (2017に策定された規格)

#Link
1. https://github.com/shoeisha-books/dokushu-cpp
2. https://wandbox.org/

#作法
1. 変数宣言と同時に初期化する。
2. 2011年より、1バイト = 8ビットの決まりは正式になった。その前、1byte = 9bitのシステムもあった。

# 組み込み型
1. ポインタ
    - 変数のアドレスを格納するための型をポインター型
    - ポインター型は*を付ける。
    - int* pi; // int型の変数のアドレスを格納できるポインター型の変数

2. Address Operator
    - 変数のアドレスを取得するには、変数名の前に& (address operator)を付ける。
    - Ex
        int i;
        int* pi = &i;
        
3. const

https://qiita.com/pink_bangbi/items/a36617bf1d5923743d69

```
    int value = 42;
    // ポインタが指してる実体を変更することができない
    const int* p = &value;
    p = &value;                   // OK
    *p = 10;                      // NG

    // ポインタ変数そのものを変更することができない
    int* const p2 = &value;
    p2 = &value;                  // NG
    *p2 = 10;                     // OK
```
メモ：
- const int* → ポインタが指してる実体を書き換えることができない
- * の後に const を付けた場合はポインタ変数そのものが不変になる
    
5. 配列
    - 定義 
        - int array[5] = {1, 2, 3, 4, 5};
        - int array[] = {1, 2, 3, 4, 5};
    - コピー
        - 各要素を個別にコピーする必要がある。

6. 文字列
    - char hello[] = "Hello";
    - 文字列は最後いｎ必ずヌル文字を入れる決まりがある。
        - char array[6] = {'a','r','r','r','r'}; // OK
        
    - std::string: 代入する文字列の長さに応じて自動で長さが変わる  
    
7. 構造体、共用体、列挙体
    - 構造体は型になって、コンストラクタには、new が必要ない。    
    - 列挙型
        - syntax: enum class
        - スコープ解決演算子: ::
            - Ex: enum class Category
            {
            Value1,
            Value2
            } 
            Category cat = Category::Value2;
            
8. クラス
    - クラスと関連づけられた関数のことはメンバー関数 (member functions)
    - インスタンスの生成には、new が不要
    
9. 参照
    - 参照とは、簡単に説明すると、[変数に別名を付ける機能]
    - 参照とポイントの違い

10. 型推論
    - cách dùng giống var trong C#
    - Ex: auto d = 3.14;
    
11. 型に別の名前を与える
   - dùng using　(giống typedef trong C)
   - Ex
        - using integer = int;
        - integer a = 20;
        
   - thường dùng cho ネスト型名
   
12. 関数オーバーロード

13. デフォルト引数
    - giống python
    
14. ラムダ式
    - コールバック関数を登録するような場合は協力な機能
    
15. 変数のコピーキャプチャ
    - クロージャ (閉包)
   
        
# Exceptions
1. try, catch, throw     
2. catch: type をdefineする必要がある。

# Files
1. #include <fstream>

         
    