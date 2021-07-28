#include <iostream>

using namespace std;

class Account {};

class SavingAccount : public Account {};
class CurrentAccount : public Account {};

class Dialog {
public:
	virtual void Display() = 0;
};

class SavingDialog : public Dialog {
public:
	void Display()
	{
		cout << "SavingDialog" << endl;
	}
};
class CurrentDialog : public Dialog {

public:
	void Display()
	{
		cout << "CurrentDialog" << endl;
	}
};

class Creator {
public:
	virtual Account* CreateAccount() = 0;
	virtual Dialog* CreateDialog() = 0;
};

class SavingCreator : public Creator {
public:
	Account* CreateAccount()
	{
		return new SavingAccount();
	}

	Dialog* CreateDialog()
	{
		return new SavingDialog();
	}
};

class CurrentCreator : public Creator {
public:
	Account* CreateAccount()
	{
		return new CurrentAccount();
	}

	Dialog* CreateDialog()
	{
		return new CurrentDialog();
	}
};

void ShowUI(Creator* creator)
{
	Account* account = creator->CreateAccount();
	Dialog* dialog = creator->CreateDialog();
	dialog->Display();
}

int main()
{
	ShowUI(new SavingCreator());
	return 0;
}
