# The Module Search Path
1. The directory from which the input script was run or the current directory if the interpreter is being run interactively
2. The list of directories contained in the PYTHONPATH environment variable, if it is set. (The format for PYTHONPATH is OS-dependent but should mimic the PATH environment variable.)
3. An installation-dependent list of directories configured at the time Python is installed (例: anaconda)

# Import syntax
1. From
    - From pkg impot mod
    - From pkg.mod import ABC
    - From pkg import mod.AB

2. Import
    - Import pkg.mod
    
# Package Initialization
1. If a file named __init__.py is present in a package directory,  
it is invoked when the package or a module in the package is imported.
    

# いつ、from module import を使うべきなのだろうか？

1. もしも、あなたがアトリビュートやメソッドにしばしばアクセスする予定であり、
何度も何度もモジュール名を打ち込みたくないのであれば、from module import を使うべきであろう。
1. もしも、いくつかのアトリビュートやメソッドを選んでインポートし、
他を必要としないのであれば、from module import　を用いればよい。
1. もしも、インポートしたいモジュールのアトリビュートや関数の中に、あなたが既に使っているアトリビュートや関数
と同一の名称のものが含まれている場合は、名前のコンフリクトを避けるため、import module を使うべきである

# Refs
1. https://sites.google.com/site/diveintopythonjp/home/5-obujekuto-to-obujekuto-shikou/5-2-from-module-import-niyoru-mojuru-no-in-poto
1. https://realpython.com/python-modules-packages/


