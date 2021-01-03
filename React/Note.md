# Reactとは
1. UIを作るためのJavaScript用ライブラリ
2. Facebook、Yahoo、ATOM、Airbnbなど、名だたる有名な企業で採用されています。

# コンセプト
1. Declarative
2. Component-Based
3. Learn Once, Write Anywhere

# 特徴
1. レンダリングが高速
2. 大規模なアプリケーションほど向いている
3. SPAのアプリケーションに向いている

# 歴史
1. 2011 Facebook AdsのUI開発するためのプロジェクトでスタート
2. 2012 OSS化
3. 2013
    - Ruby on rails, pythonでのサポート
    
4. 2014
    - material-uiのRelease
    
5. 2015
    - react nativeのRelease
    - ReduxのRelease
    
6. 2017
    - React Fiberの発表
    
7. 2018
    - v16.3.0のRelease: ContextApi, createRef
    
8. 2019
    - V17.8.0のRelease: ReactHooks
   
# React tutorial
1. Component 
   - a component takes in parameters, called props (properties) and returns a hierarchy of views to display via the 
     render method.
   - React components can have state by setting this.state in their constructors. this.state should be considered 
       as private to a React component that it’s defined in
   - State
      - when you call setState in a component, React automatically updates the child components inside of it too.
      - To collect data from multiple children, or to have two child components communicate with each other, 
        you need to declare the shared state in their parent component instead. 
        The parent component can pass the state back down to the children by using props; 
        this keeps the child components in sync with each other and with the parent component.
        
   - props, stateの違い
      - State: そのコンポーネントが持っている状態
         - mutable data (可変のデータ)
      - Props: 親コンポーネントから渡されたプロパティ
         - immutable data 
   
2. Render 
   - returns a description of what you want to see on the screen.  
   - In particular, render returns a React element, which is a lightweight description of what to render. 
   Most React developers use a special syntax called “JSX” which makes these structures easier to write. 
   The <div /> syntax is transformed at build time to React.createElement('div'). 
   
3. jsx = javascript extension. 
   - by using JSX you can write concise HTML/XML-like structures 
   (e.g., DOM like tree structures) in the same file as you write JavaScript code, 
   then Babel will transform these expressions into actual JavaScript code
   
4. Passing Data through props

# Redux
1. store
   - storeはreduxが管理してる値です。アプリケーションの状態(state)を保持します。
   
2. store, props, stateの使い分け
   - app全体で管理したい値はstore管理、コンポーネント毎に管理したい値はprops or stateで管理する。
   - 親から子へデータを渡す時はprops、状態を更新させる時はstateを使う。

# Webpackとは
1. webpackは指定されたファイルを起点として、そこからimport文を頼りに芋づる式にファイルを繋げてゆき、
   一つにまとめたJavaScriptファイルを出力します。
   このまとめる処理はバンドル(bundle)と呼ばれています。（束ねるの意）そしてバンドルを行うツールはバンドラーと呼ばれています。
   ポイントは、“基本機能はあくまで一つのJavaScriptファイルにまとめる”というところです。
   
2. Babelは、ES6やES7の機能や構文を、ES5相当の機能を使ってブラウザで実行できるように変換します。
   ES5は現在広く使われているブラウザのほとんどでサポートされています。ES5の機能であれば、現状でも問題なく使うことができます。
   
# Tools
1. React Devtools extension for Chrome and Firefox