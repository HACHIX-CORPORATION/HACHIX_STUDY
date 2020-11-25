#include <iostream>

enum class Category
{
	Value1,
	Value2
};

class C
{
public:
	int public_member;
	int get_id();

private:
	int private_member;
};

int C::get_id()
{
	return 1;
}

int main() {
	std::cout << "Hello, World";

	Category cat = Category::Value2;

	// 列挙体の値に対応した整数を得る
	std::cout << static_cast<int>(cat) << std::endl;

	// クラスのインスタンス
	C c;
	c.public_member = 1;

	// 参照は変数に別名を付ける機能
	int test = 42;

	int& referenceTest = test;	// 変数valueへの参照
	referenceTest = 0; // 参照を使って変数valueの値を書き換える。

	// ポインターと参照違いのコード
	// pointerは、代入前後で指し示すアドレスが変化しています。
	// 一方referenceにotherを代入しても、otherが持つ値がvalueに格納されるだけで、参照が指し示すアドレスには変化が無い。
	int value = 42;
	int other = 0;
	int* pointer = &value;
	int& reference = value;

	std::cout << "pointerの持つアドレスは " << pointer << "です" << std::endl;
	std::cout << "referenceの持つアドレスは" << &reference << "です" << std::endl;

	pointer = &other;
	reference = other;

	std::cout << "pointerの持つアドレスは " << pointer << "です" << std::endl;
	std::cout << "referenceの持つアドレスは" << &reference << "です" << std::endl;

	// 配列のループ
	int array2[] = {0,1,2,3};

	for (auto e : array2)
	{
		std::cout << e << std::endl;
	}

	// ラムダ式
	auto show = [](int i) -> void
	{
		std::cout << i << std::endl;
	};
	show(42);

	return 0;
}