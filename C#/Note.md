# Kiến thức cơ bản về C#
## History
1. 2000年: 共通の実行環境や言語への非依存性等を目標に基づいて[.Net Framework]を開発しました。
2. C# Version
    - C#2.0: ジェネリック、イテレータ
    - C#3.0: LINQ
    - C#4.0: dynamic, COMの相互運用
    - C#5.0: 非同期メソッド
    - C#6.0: オープンソース化
3. C#応用
    - 業務系アプリ
    - ゲーム (Unity)

## Những kiến thức cơ bản so sánh với python
1. https://hiroronn.hatenablog.jp/entry/20170717/1500281854

2. Bổ sung
    - クラス
        - Python: クラス変数, クラスメソッド -> C#: static 変数、static メソッド
    
## Những khái niệm của C#
1. Generic
https://viblo.asia/p/su-dung-generics-trong-c-924lJDvNKPM

2. LINQ: Language Integrated Query
https://www.tutorialsteacher.com/linq/what-is-linq

## 1 vài quiz
1. ref với out khác nhau như thế nào
https://pond-comfat.hatenablog.com/entry/2019/03/03/015457

## Link tham khảo
1. https://docs.google.com/document/d/1u07-Q83wEQWI0pfe5_0eloKh7T8cheK_0PFicI96aeA/edit?usp=sharing

# Kiến thức nâng cao 

## Delegates
1. An object that knows how to call a method ( or a group of methods)
2. A reference to a function

## Lambda
1. No access modifier
2. No name
3. No return statement
    - Ex: args => expression
    - () => ...
    - x => ...
    - (x, y, z) => ...
    
## Event And Delegate
1. Events
    - A mechanism for communication between objects
    - Used in building Loosely Coupled Applications
    - Helps extending applications

2. Delegates
    - Agreement / Contract between Pub and Sub
    - Determines the signature of the event handler method in Sub
    
## .Net Framework, .Net Standard, .Net Core
- link
    - https://blog.hiros-dot.net/?p=9086
    - https://qiita.com/mtm3qi/items/28cd4c2da77008b0892c
- .Net Standardは仕様であり、.Net Framework, .Net Core, Xamarin　それぞれのベースとなるクラスを定義する。
- .Net Core
    - クロスプラットフォームに対応するために後から生まれた。
    - Windows, Linux, MacOS向けのフレームワーク
    - 新規開発の場合は.Net Coreでいい

- .Net 5
    - 2020年11月に .Net 5がリリースされて、Framework, Coreは一つに統合された。  
    
- Magic Onion
    - Server: .NET 5.0+, .NET Core 3.2
    - Client: .NET Standard 2.1, .NET Standard 2.0
