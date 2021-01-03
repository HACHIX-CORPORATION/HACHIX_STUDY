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
1. a component takes in parameters, called props (properties) and returns a hierarchy of views to display via the 
render method.
   
2. The render method returns a description of what you want to see on the screen.  
   In particular, render returns a React element, which is a lightweight description of what to render. 
   Most React developers use a special syntax called “JSX” which makes these structures easier to write. 
   The <div /> syntax is transformed at build time to React.createElement('div'). 
   
3. jsx = javascript extension. by using JSX you can write concise HTML/XML-like structures 
   (e.g., DOM like tree structures) in the same file as you write JavaScript code, 
   then Babel will transform these expressions into actual JavaScript code
   
4. Passing Data through props
   