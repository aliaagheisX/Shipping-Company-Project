#include "UI.h"

void UI::Output(string s)
{
	cout << s<<"\n";
}

void UI::Line()
{
	for (int i = 0; i < 50; i++)
	{
		cout << "-";
	}
	cout << "\n";
}
