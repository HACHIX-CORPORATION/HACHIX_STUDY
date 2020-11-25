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

	// �񋓑̂̒l�ɑΉ����������𓾂�
	std::cout << static_cast<int>(cat) << std::endl;

	// �N���X�̃C���X�^���X
	C c;
	c.public_member = 1;

	// �Q�Ƃ͕ϐ��ɕʖ���t����@�\
	int test = 42;

	int& referenceTest = test;	// �ϐ�value�ւ̎Q��
	referenceTest = 0; // �Q�Ƃ��g���ĕϐ�value�̒l������������B

	// �|�C���^�[�ƎQ�ƈႢ�̃R�[�h
	// pointer�́A����O��Ŏw�������A�h���X���ω����Ă��܂��B
	// ���reference��other�������Ă��Aother�����l��value�Ɋi�[����邾���ŁA�Q�Ƃ��w�������A�h���X�ɂ͕ω��������B
	int value = 42;
	int other = 0;
	int* pointer = &value;
	int& reference = value;

	std::cout << "pointer�̎��A�h���X�� " << pointer << "�ł�" << std::endl;
	std::cout << "reference�̎��A�h���X��" << &reference << "�ł�" << std::endl;

	pointer = &other;
	reference = other;

	std::cout << "pointer�̎��A�h���X�� " << pointer << "�ł�" << std::endl;
	std::cout << "reference�̎��A�h���X��" << &reference << "�ł�" << std::endl;

	// �z��̃��[�v
	int array2[] = {0,1,2,3};

	for (auto e : array2)
	{
		std::cout << e << std::endl;
	}

	// �����_��
	auto show = [](int i) -> void
	{
		std::cout << i << std::endl;
	};
	show(42);

	return 0;
}