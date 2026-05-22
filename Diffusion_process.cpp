#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

using namespace std;
using namespace sf;

bool is_allowed(int i, int j)
{
	if (i < 0 || j < 0 || i > 101 || j > 101) return false;
	return true;
}

bool is_border(int i, int j)
{
	if (is_allowed(i, j) == 0) return 0;
	if (i == 0 || j == 0 || i == 101 || j == 101) return true;
	return false;
}


// структуры

struct field_bool
{
	bool particle;
	bool is_border;
};

struct field
{
	int particles;
	double k;
	bool is_border;
};


// bool

void left_rotate(field_bool a[102][102], int i, int j)
{
	bool p1, p2, p3, p4;

	p1 = a[i][j].particle;
	p2 = a[i][j + 1].particle;
	p3 = a[i + 1][j + 1].particle;
	p4 = a[i + 1][j].particle;

	a[i][j].particle = p4;
	a[i][j + 1].particle = p1;
	a[i + 1][j + 1].particle = p2;
	a[i + 1][j].particle = p3;

	if (is_border(i, j))
	{
		a[i][j].particle = 0;

	}


	if (is_border(i, j + 1))
	{
		a[i][j + 1].particle = 0;

	}

	if (is_border(i + 1, j + 1))
	{
		a[i + 1][j + 1].particle = 0;

	}

	if (is_border(i + 1, j))
	{
		a[i + 1][j].particle = 0;

	}

}

void right_rotate(field_bool a[102][102], int i, int j)
{
	bool p1, p2, p3, p4;

	p1 = a[i][j].particle;
	p2 = a[i + 1][j].particle;
	p3 = a[i + 1][j + 1].particle;
	p4 = a[i][j + 1].particle;

	a[i][j].particle = p4;
	a[i + 1][j].particle = p1;
	a[i + 1][j + 1].particle = p2;
	a[i][j + 1].particle = p3;

	if (is_border(i, j))
	{
		a[i][j].particle = 0;

	}


	if (is_border(i, j + 1))
	{
		a[i][j + 1].particle = 0;

	}

	if (is_border(i + 1, j + 1))
	{
		a[i + 1][j + 1].particle = 0;

	}

	if (is_border(i + 1, j))
	{
		a[i + 1][j].particle = 0;

	}

}

void rotate(field_bool a[102][102], int i, int j)
{
	int probability = rand() % 2;

	bool b1, b2, b3, b4;
	b1 = a[i][j].is_border;
	b2 = a[i + 1][j].is_border;
	b3 = a[i + 1][j + 1].is_border;
	b4 = a[i][j + 1].is_border;

	if ((b1 || b2 || b3 || b4) == false)
	{
		if (probability == 0)
		{
			left_rotate(a, i, j);
		}
		else
		{
			right_rotate(a, i, j);
		}
	}
		
}

void change_the_world(field_bool a[102][102])
{
	for (int i = 0; i < 102; i += 2)
		for (int j = 0; j < 102; j += 2)
		{
			rotate(a, i, j);
		}

	for (int i = 1; i < 100; i += 2)
		for (int j = 1; j < 100; j += 2)
		{
			rotate(a, i, j);
		}
}

void display(field_bool a[102][102])
{
	RenderWindow window(VideoMode(918, 918), "Diffusion");
	RectangleShape rect(Vector2f(7, 7));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		window.clear(Color::White);

		for (int i = 0; i < 102; i++)
			for (int j = 0; j < 102; j++)
			{
				if (a[i][j].particle || a[i][j].is_border) rect.setFillColor(Color(0, 0, 0));
				else rect.setFillColor(Color(255, 255, 255));
				rect.setPosition(i * 9, j * 9);
				window.draw(rect);
			}

		window.display();

	}
}

void visualization(field_bool a[102][102])
{
	RenderWindow window(VideoMode(918, 918), "Diffusion");
	RectangleShape rect(Vector2f(7, 7));
	rect.setFillColor(Color(255, 0, 0));

	int t = 0;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}


		window.clear(Color::White);


		for (int i = 0; i < 102; i++)
			for (int j = 0; j < 102; j++)
			{
				if (a[i][j].particle || a[i][j].is_border) rect.setFillColor(Color(0, 0, 0));
				else rect.setFillColor(Color(255, 255, 255));
				rect.setPosition(i * 9, j * 9);
				window.draw(rect);
			}

		window.display();


		change_the_world(a);

		if (t % 100 == 0) cout << t << endl;
		t++;
	}


}

void simulation(field_bool a[102][102],int iterations = 5000,bool visualization = true) 
{
	int t = 0;

	if (visualization) 
	{
		RenderWindow window(VideoMode(918, 918), "Diffusion");
		RectangleShape rect(Vector2f(7, 7));
		rect.setFillColor(Color(255, 0, 0));


		while (window.isOpen())
		{
			
			Event event;
			// обработка закрытия окна пользователем
			window.clear(Color::White);
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window.close();
				}
			}

			// Закрытие окна, если итерация превышает лимит. Используется continue, чтобы избежать выполнения функции, меняющей состояние системы.
			if (t > iterations) 
			{
				window.close();
				continue;
			}
				

			for (int i = 0; i < 102; i++)
				for (int j = 0; j < 102; j++)
				{
					if (a[i][j].particle || a[i][j].is_border) rect.setFillColor(Color(0, 0, 0));
					else rect.setFillColor(Color(255, 255, 255));
					rect.setPosition(i * 9, j * 9);
					window.draw(rect);
				}

			window.display();
			change_the_world(a);
			if (t % 100 == 0) cout << t << endl;
			t++;
		}
	}
	else 
	{
		while (t <= iterations)
		{
			change_the_world(a);
			if (t % 100 == 0) cout << t << endl;
			t++;
		}
	}
	
	display(a);

}

void set_field(field_bool a[102][102], bool border = false, int source = 2)
{
	for (int i = 0; i < 102; i++)
		for (int j = 0; j < 102; j++)
		{
			a[i][j].particle = 0;
			a[i][j].is_border = 0;
		}


	switch (source)
	{
	case 2:
		for (int i = 35; i < 65; i++)
			for (int j = 35; j < 65; j++)
			{
				a[i][j].particle = 1;
			}
		break;
	case 1:
		for (int i = 40; i < 60; i++)
			for (int j = 40; j < 60; j++)
			{
				a[i][j].particle = 1;
			}
		break;
	case 0:
		for (int i = 45; i < 55; i++)
			for (int j = 45; j < 55; j++)
			{
				a[i][j].particle = 1;
			}
		break;
	default:
		for (int i = 35; i < 65; i++)
			for (int j = 35; j < 65; j++)
			{
				a[i][j].particle = 1;
			}
		break;
	}
	// Блок границы
	if (border)
	{
		for (int i = 0; i < 102; i++)
		{
			a[i][0].is_border = 1;
			a[i][101].is_border = 1;
			a[0][i].is_border = 1;
			a[101][i].is_border = 1;
		}
	}
		
}

// Осреднение для одной клетки
void averaging(field_bool a[102][102], field b[102][102], int i, int j, int r)
{

	int Sum = 0;
	int k = 0;
	for (int x = i - r; x <= i + r; x++)
		for (int y = j - r; y <= j + r; y++)
		{
			if (is_allowed(x, y) && !is_border(x, y))
			{
				if (a[x][y].particle == 1) Sum += 1;
				k++;
			}
		}

	b[i][j].particles = ceil(1000 * ((Sum + 0.0) / k));

}

// int

void left_rotate(field a[102][102], int i, int j)
{
	int p1, p2, p3, p4;

	if (is_border(i, j))
	{
		a[i][j].particles = 0;
		p1 = 0;
	}
	else p1 = a[i][j].particles;

	if (is_border(i, j + 1))
	{
		a[i][j + 1].particles = 0;
		p2 = 0;
	}
	else p2 = a[i][j + 1].particles;

	if (is_border(i + 1, j + 1))
	{
		a[i + 1][j + 1].particles = 0;
		p3 = 0;
	}
	else p3 = a[i + 1][j + 1].particles;

	if (is_border(i + 1, j))
	{
		a[i + 1][j].particles = 0;
		p4 = 0;
	}
	else p4 = a[i + 1][j].particles;



	int temp1 = floor(p1 * a[i][j].k);
	int temp2 = floor(p2 * a[i][j + 1].k);
	int temp3 = floor(p3 * a[i + 1][j + 1].k);
	int temp4 = floor(p4 * a[i + 1][j].k);

	int tp1 = p1 - temp1 + temp4;
	int tp2 = p2 - temp2 + temp1;
	int tp3 = p3 - temp3 + temp2;
	int tp4 = p4 - temp4 + temp3;


	if (is_border(i, j)) a[i][j].particles = 0;
	else a[i][j].particles = tp1;

	if (is_border(i, j + 1)) a[i][j + 1].particles = 0;
	else a[i][j + 1].particles = tp2;

	if (is_border(i + 1, j + 1)) a[i + 1][j + 1].particles = 0;
	else a[i + 1][j + 1].particles = tp3;

	if (is_border(i + 1, j)) a[i + 1][j].particles = 0;
	else a[i + 1][j].particles = tp4;

}

void right_rotate(field a[102][102], int i, int j)
{
	int p1, p2, p3, p4;

	if (is_border(i, j))
	{
		a[i][j].particles = 0;
		p1 = 0;
	}
	else p1 = a[i][j].particles;

	if (is_border(i + 1, j))
	{
		a[i + 1][j].particles = 0;
		p2 = 0;
	}
	else p2 = a[i + 1][j].particles;

	if (is_border(i + 1, j + 1))
	{
		a[i + 1][j + 1].particles = 0;
		p3 = 0;
	}
	else p3 = a[i + 1][j + 1].particles;

	if (is_border(i, j + 1))
	{
		a[i][j + 1].particles = 0;
		p4 = 0;
	}
	else p4 = a[i][j + 1].particles;



	int temp1 = floor(p1 * a[i][j].k);
	int temp2 = floor(p2 * a[i + 1][j].k);
	int temp3 = floor(p3 * a[i + 1][j + 1].k);
	int temp4 = floor(p4 * a[i][j + 1].k);

	int tp1 = p1 - temp1 + temp4;
	int tp2 = p2 - temp2 + temp1;
	int tp3 = p3 - temp3 + temp2;
	int tp4 = p4 - temp4 + temp3;


	if (is_border(i, j)) a[i][j].particles = 0;
	else a[i][j].particles = tp1;

	if (is_border(i + 1, j)) a[i + 1][j].particles = 0;
	else a[i + 1][j].particles = tp2;

	if (is_border(i + 1, j + 1)) a[i + 1][j + 1].particles = 0;
	else a[i + 1][j + 1].particles = tp3;

	if (is_border(i, j + 1)) a[i][j + 1].particles = 0;
	else a[i][j + 1].particles = tp4;

}

void rotate(field a[102][102], int i, int j)
{

	int probability = rand() % 2;
	bool b1, b2, b3, b4;
	b1 = a[i][j].is_border;
	b2 = a[i + 1][j].is_border;
	b3 = a[i + 1][j + 1].is_border;
	b4 = a[i][j + 1].is_border;

	if ((b1 || b2 || b3 || b4) == false)
	{
		if (probability == 0)
		{
			left_rotate(a, i, j);
		}
		else
		{
			right_rotate(a, i, j);
		}
	}
}

void change_the_world(field a[102][102])
{
	for (int i = 0; i < 102; i += 2)
		for (int j = 0; j < 102; j += 2)
		{
			rotate(a, i, j);
		}

	for (int i = 1; i < 100; i += 2)
		for (int j = 1; j < 100; j += 2)
		{
			rotate(a, i, j);
		}
}

void display(field a[102][102])
{
	RenderWindow window(VideoMode(918, 918), "Diffusion");
	RectangleShape rect(Vector2f(7, 7));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		window.clear(Color::Black);

		for (int i = 0; i < 102; i++)
			for (int j = 0; j < 102; j++)
			{
				if (a[i][j].is_border == false)
				{
					int temp = a[i][j].particles / 100;
					switch (temp)
					{
					case 10:
					case 9:
						rect.setFillColor(Color(0, 0, 0));
						break;
					case 8:
						rect.setFillColor(Color(25, 25, 25));
						break;
					case 7:
						rect.setFillColor(Color(50, 50, 50));
						break;
					case 6:
						rect.setFillColor(Color(75, 75, 75));
						break;
					case 5:
						rect.setFillColor(Color(100, 100, 100));
						break;
					case 4:
						rect.setFillColor(Color(125, 125, 125));
						break;
					case 3:
						rect.setFillColor(Color(150, 150, 150));
						break;
					case 2:
						rect.setFillColor(Color(175, 175, 175));
						break;
					case 1:
						rect.setFillColor(Color(200, 200, 200));
						break;
					case 0:
						if (a[i][j].particles == 0) rect.setFillColor(Color(255, 255, 255));
						else rect.setFillColor(Color(225, 225, 225));
						break;
					}
					//if (a[i][j].particles > 1000)rect.setFillColor(Color(0, 0, 0));
				}
				else rect.setFillColor(Color(0, 0, 0));
				rect.setPosition(i * 9, j * 9);
				window.draw(rect);

			}

		window.display();

	}
}

void visualization(field a[102][102])
{
	RenderWindow window(VideoMode(918, 918), "Diffusion");
	RectangleShape rect(Vector2f(7, 7));

	int t = 0;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}


		window.clear(Color::Black);


		for (int i = 0; i < 102; i++)
			for (int j = 0; j < 102; j++)
			{
				if (a[i][j].is_border == false)
				{
					int temp = a[i][j].particles / 100;
					switch (temp)
					{
					case 10:
					case 9:
						rect.setFillColor(Color(0, 0, 0));
						break;
					case 8:
						rect.setFillColor(Color(25, 25, 25));
						break;
					case 7:
						rect.setFillColor(Color(50, 50, 50));
						break;
					case 6:
						rect.setFillColor(Color(75, 75, 75));
						break;
					case 5:
						rect.setFillColor(Color(100, 100, 100));
						break;
					case 4:
						rect.setFillColor(Color(125, 125, 125));
						break;
					case 3:
						rect.setFillColor(Color(150, 150, 150));
						break;
					case 2:
						rect.setFillColor(Color(175, 175, 175));
						break;
					case 1:
						rect.setFillColor(Color(200, 200, 200));
						break;
					case 0:
						if (a[i][j].particles == 0) rect.setFillColor(Color(255, 255, 255));
						else rect.setFillColor(Color(225, 225, 225));
						break;
					}
					//if (a[i][j].particles > 1000)rect.setFillColor(Color(0, 0, 0));
				}
				else rect.setFillColor(Color(0, 0, 0));
				rect.setPosition(i * 9, j * 9);
				window.draw(rect);

			}

		window.display();

		change_the_world(a);

		if (t % 100 == 0)
		{
			cout << t << endl;
			//display(a);
		}
		t++;
	}

}

void simulation(field a[102][102], int iterations = 5000, bool visualization = true)
{
	int t = 0;

	if (visualization)
	{
		RenderWindow window(VideoMode(918, 918), "Diffusion");
		RectangleShape rect(Vector2f(7, 7));
		rect.setFillColor(Color(255, 0, 0));


		while (window.isOpen())
		{

			Event event;
			// обработка закрытия окна пользователем
			window.clear(Color::Black);
			//window.clear(Color::White);
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window.close();
				}
			}

			// Закрытие окна, если итерация превышает лимит. Используется continue, чтобы избежать выполнения функции, меняющей состояние системы.
			if (t > iterations)
			{
				window.close();
				continue;
			}


			for (int i = 0; i < 102; i++)
				for (int j = 0; j < 102; j++)
				{
					if (a[i][j].is_border == false)
					{
						int temp = a[i][j].particles / 100;
						switch (temp)
						{
						case 10:
						case 9:
							rect.setFillColor(Color(0, 0, 0));
							break;
						case 8:
							rect.setFillColor(Color(25, 25, 25));
							break;
						case 7:
							rect.setFillColor(Color(50, 50, 50));
							break;
						case 6:
							rect.setFillColor(Color(75, 75, 75));
							break;
						case 5:
							rect.setFillColor(Color(100, 100, 100));
							break;
						case 4:
							rect.setFillColor(Color(125, 125, 125));
							break;
						case 3:
							rect.setFillColor(Color(150, 150, 150));
							break;
						case 2:
							rect.setFillColor(Color(175, 175, 175));
							break;
						case 1:
							rect.setFillColor(Color(200, 200, 200));
							break;
						case 0:
							if (a[i][j].particles == 0) rect.setFillColor(Color(255, 255, 255));
							else rect.setFillColor(Color(225, 225, 225));
							break;
						}
						//if (a[i][j].particles > 1000)rect.setFillColor(Color(0, 0, 0));
					}
					else rect.setFillColor(Color(0, 0, 0));
					rect.setPosition(i * 9, j * 9);
					window.draw(rect);

				}
			window.display();
			change_the_world(a);
			if (t % 100 == 0) cout << t << endl;
			t++;
		}
	}
	else
	{
		while (t <= iterations)
		{
			change_the_world(a);
			if (t % 100 == 0) cout << t << endl;
			t++;
		}
	}

	display(a);

}

void set_field(field a[102][102], bool border = false, int source = 2)
{
	for (int i = 0; i < 102; i++)
		for (int j = 0; j < 102; j++)
		{
			a[i][j].particles = 0;
			a[i][j].k = 0.1;
			a[i][j].is_border = false;
		}
	
	switch (source)
	{
	case 2:
		for (int i = 35; i < 65; i++)
			for (int j = 35; j < 65; j++)
			{
				a[i][j].particles = 1000;
			}
		break;
	case 1:
		for (int i = 40; i < 60; i++)
			for (int j = 40; j < 60; j++)
			{
				a[i][j].particles = 1000;
			}
		break;
	case 0:
		for (int i = 45; i < 55; i++)
			for (int j = 45; j < 55; j++)
			{
				a[i][j].particles = 1000;
			}
		break;
	default:
		for (int i = 35; i < 65; i++)
			for (int j = 35; j < 65; j++)
			{
				a[i][j].particles = 1000;
			}
		break;
	}

	// Блок границы
	if (border)
	{
		for (int i = 0; i < 102; i++)
		{
			a[i][0].is_border = 1;
			a[i][101].is_border = 1;
			a[0][i].is_border = 1;
			a[101][i].is_border = 1;
		}
	}
	
}

// осреднение всего клеточного автомата b
void get_averaging(field a[102][102], field_bool b[102][102], int r)
{

	for (int i = 0; i < 102; i++)
		for (int j = 0; j < 102; j++)
		{
			averaging(b, a, i, j, r);
		}

	display(a);
}



int main()
{
	bool mode = 1;
	bool border = 1;
	bool visualization = 1;
	int source = 2;
	int iterations = 2000;
	int r = 7;
	cout << "Select the operating mode: Single-particle / Multi-particle (1/0):" << endl;
	cin >> mode;
	
	if (mode)
	{
		field_bool b[102][102];
		field c[102][102];
		set_field(c);
		cout << "Select the border operating mode: Closed / Open (1/0):" << endl;
		cin >> border;
		cout << "Select Substance Source Size (0/1/2):" << endl;
		cin >> source;
		set_field(b,border, source);
		cout << "Enter the number of iterations: " << endl;
		cin >> iterations;
		cout << "Select Rendering Mode: 0 - Only the result, 1 - Every step: " << endl;
		cin >> visualization;
		simulation(b, iterations, visualization);
		cout << "Enter the averaging radius: " << endl;
		cin >> r;

		while ((r < 0) || (r >= 100))
		{
			cout << "Enter the averaging radius: " << endl;
			cin >> r;
		}
		get_averaging(c, b, r);
	}
	else
	{
		field a[102][102];
		cout << "Select the border operating mode: Closed / Open (1/0):" << endl;
		cin >> border;
		cout << "Select Substance Source Size (0/1/2):" << endl;
		cin >> source;
		set_field(a, border, source);
		cout << "Enter the number of iterations: " << endl;
		cin >> iterations;
		cout << "Select Rendering Mode: 0 - Only the result, 1 - Every step: " << endl;
		cin >> visualization;
		simulation(a, iterations, visualization);
	}

}


