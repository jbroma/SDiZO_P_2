#include "stdafx.h"
#include "List.h"
#include "Queue.h"
#include "Vertex.h"
#include "ConsoleNav.h"
#include <iostream>
#include <windows.h>
//#include <vld.h>			// Memory leak testing

int main()
{
	bool tests = true;
	
	if (tests) {
		Queue<Vertex> q1;
		Vertex v1, v2, v3, v4;
		/*v1 = new Vertex();
		v2 = new Vertex();*/
		q1.enqueue(Vertex());
		q1.enqueue(Vertex());
		std::cout << q1.isEmpty() << std::endl;
		//std::cout << q1.dequeue()->i << std::endl << q1.dequeue()->j << std::endl;	
		std::cout << q1.isEmpty() << std::endl;
		v1 = q1.dequeue();
		v2 = q1.dequeue();
		system("Pause");
		

		List<Vertex> li;
		li.pushFront(Vertex(1, 5));
		li.pushFront(Vertex(2, 6));
		li.pushFront(Vertex(3, 7));

		for (Vertex v : li) {
			std::cout << " => " << v.toString();
		}
		std::cout << std::endl;

		system("Pause");
	}
	
	// menu part
	/*while (true) {
		int menu_choice = menu(40, 10, "Select Mode", 3, "Manual Testing", "Time Testing", "Exit");
		system("cls");

		switch (menu_choice) {
		case 1: manual_menu(); break;
		case 2: tests_menu(); break;
		case 3: return 0;
		}
	}*/


    return 0;
}

