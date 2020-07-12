#include <iostream>

using namespace std;
// Двойной список
template<typename T>
class List
{
public:
	List(); // консруктор листа
	~List(); // деструктор листа
	
	int Getsize() { return size; } // кол-во хранилищ 

	T &  operator[](const int index); //оператор [] 
	
	void push_back(T data); // добавить в элемент в конец

	void push_front(T data); // добавить элемент в начало

	void insert(T data, int index); // добавить элемент в указанное место

	void pop_back(); // удалить элемент из конца

	void pop_front(); // удалить элемент из начала
	
	void removeAT(int index); // удалить указанный элемент 

	void clear(); // удалить все элементы

	void printH(List<T> &obj); // вывод с головы
	
	void printT(List<T> &obj); // вывод с хвоста 

private:

	template<typename T> // класс хранилище
	class Node // класс хранилище
	{
	public:
		T data;
		Node *pNext, *pBack;

		Node(T data = T(), Node *pNext = nullptr, Node *pBack = nullptr) // конструктор хранилища
		{
			this->data = data; // информация
			this->pNext = pNext; // указатель на след. хранилище
			this->pBack = pBack; // указатель на предыдущее хранилище
		}
	};
	
	Node<T> *head; // объект хранилиша голова
	Node<T> *tail; // объект хранилища хвост
	int size; // кол-во хранилищ
};

template<typename T> // конструктор листа
List<T>::List() // конструктор листа
{
	size = 0;
	head = nullptr; // пустая "голова"
	tail = nullptr; // пустой "хвост"
}

template<typename T> // деструктор литса
List<T>::~List() // деструктор литса
{
	clear(); // удаление всех хранилищ
}

template<typename T> // оператор [] 
T & List<T>::operator[](const int index) // оператор [] 
{
	int indexmax = size - 1, indexmin = 0; // крайние возможные индексы данного массива
	indexmax -= index; // мин. кол-во шагов, прежде чем добрать до хранилища из хвоста
	indexmin += index; // мин. кол-во шагов, прежде чем добрать до хранилища из головы

	if (indexmin < indexmax || indexmin == indexmax)
	{
		int counter = 0; // номер хранилище, в котором находимся
		Node<T> *current = this->head;
		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->data;
			}
			current = current->pNext;
			counter++;
		}
	}
	else if (indexmin > indexmax)
	{
		int counter = size - 1; // номер хранилище, в котором находимся
		Node<T> *current = this->tail;
		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->data;
			}
			current = current->pBack;
			counter--;
		}
	}
}
	
template<typename T> // добавить в элемент в конец
void List<T>::push_back(T data) // добавить в элемент в конец
{
	if (size > 1) // если есть более 1 хранилища
	{
	 Node <T> *temp = tail;
		tail = new Node <T>(data, nullptr, tail);
		temp->pNext = tail;
		int g = 89;
	}
	else if (size == 1) // если есть 1 хранилще
		{
			tail = new Node <T>(data, nullptr, tail);
			head->pNext = this->tail;
		}
	else // если хранлищ нет
		{
			head = tail = new Node <T>(data, head, tail);
		}		
	size++;	
}

template<typename T> // добавить элемент в начало
void List<T>::push_front(T data) // добавить элемент в начало
{
	if (size == 0)
	{
		head = tail = new Node <T>(data, head, tail);
	}
	else
	{
		Node<T> *current = this->head;
		head = new Node<T>(data, head, nullptr);
		current->pBack = head;
	}
	size++;
}

template<typename T> // добавить элемент в указанное место
void List<T>::insert(T data, int index) // добавить элемент в указанное место
{
	int indexmax = size - 1, indexmin = 0, resmax= size-1,resmin=0; // крайние возможные индексы данного массива
	resmax -= index; // мин. кол-во шагов, прежде чем добрать до хранилища из хвоста
	resmin += index; // мин. кол-во шагов, прежде чем добрать до хранилища из головы
	
	if (index == indexmin || index == indexmax)
	{
		if (index == indexmin)
		{push_front(data);} // если индекс первого хранилиша, выполняем метод добавить в начало
		else  
		{push_back(data);} // если индекс последнего хранилиша, выполняем метод добавить в конце
	}
	 else if (resmin < resmax || resmin == resmax)
	 {
		int counter = 0; // номер хранилище, в котором находимся
		Node<T> *current = this->head;
		while (current != nullptr)
		{
			if (counter == index)
			{
				current = new Node<T>(data, current, current->pBack);
				(current->pNext)->pBack = current; // старое хранлище в пред. указетеле указываем на новое хранилище
				(current->pBack)->pNext = current; /* в хранилище, расположенном раньше страго хранилища, в указателе на
                 на след. хранилище указыаем на новое хранилище*/
				break;
			}
			current = current->pNext;
			counter++;
		}
		size++;
	}
	else if (resmin > resmax)
	{
		int counter = size - 1; // номер хранилище, в котором находимся
		Node<T> *current = this->tail;
		while (current != nullptr)
		{
			if (counter == index)
			{
				current = new Node<T>(data, current, current->pBack);
				(current->pNext)->pBack = current;	
				(current->pBack)->pNext = current;
				break;
			}
			current = current->pBack;
			counter--;
		}
		size++;
	} 
}

template<typename T> // удалить элемент из конца
void List<T>::pop_back() // удалить элемент из конца
{
	Node<T> * current = tail;
	tail = current->pBack;
	delete current;
	if (size > 1) { tail->pNext = nullptr;} // обрубаем конец хвоста, т.е. указатель на след. хранилише
	else { head = tail; } // обнуляем голову, чтобы там не было мусора
	size--;	
}

template<typename T> // удалить элемент из начала
void List<T>::pop_front() // удалить элемент из начала
{
	Node<T> * current = head;
	head = current->pNext;
	delete current;
	if (size > 1) { head->pBack = nullptr; } // обнуляем указатель на пред. хранилище у головы
	else { tail = head; } // обнуляем хвост, чтобы там не было мусора
	size--;
}

template<typename T> // удалить указанный элемент 
void List<T>::removeAT(int index) // удалить указанный элемент 
{
	int indexmax = size - 1, indexmin = 0, resmax = size-1, resmin = 0; // крайние возможные индексы данного массива
	resmax -= index;
	resmin += index;

	if (index == indexmin || index == indexmax)
	{
		if (index == indexmin)
			pop_front();
		else
			pop_back();
	}
	else if (resmin < resmax || resmin == resmax)
	{
		int counter = 0; // номер хранилище, в котором находимся
		Node<T> *current = this->head;
		while (current != nullptr)
		{
			if (counter == index)
			{
				(current->pBack)->pNext = current->pNext;
				(current->pNext)->pBack = current->pBack;
				delete current;
				break;
			}
			current = current->pNext;
			counter++;
		}
		size--;
	}
	else if (resmin > resmax)
	{
		int counter = size - 1; // номер хранилище, в котором находимся
		Node<T> *current = this->tail;
		while (current != nullptr)
		{
			if (counter == index)
			{
				(current->pBack)->pNext = current->pNext;
				(current->pNext)->pBack = current->pBack;
				break;
			}
			current = current->pBack;
			counter--;
		}
		size--;
	}
}

template<typename T> // удалить все элементы
void List<T>::clear() // удалить все элементы
{
	while (size) // пока сайз не равен 0
	{
		pop_front();
	}
}

template<typename T> // вывод с головы
void List<T>::printH(List<T> &obj) // вывод с головы
{
	cout << "============================" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "# " << i << "\t" << (obj[i])<<"\t\t  ||"<< endl;
	}
	
	cout << "============================" << endl;

}

template<typename T> // вывод с хвоста 
void List<T>::printT(List<T> &obj) // вывод с хвоста 
{
	cout << "============================" << endl;
	for (int i = size-1; i >= 0; i--)
	{
		cout << "# " << i << "\t" << (obj[i]) << "\t\t  ||" << endl;
	}

	cout << "============================" << endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	List<int> general;
	general.push_back(2); 
	general.push_front(7); 
	general.push_back(3); 
	general.push_back(5); 
	general.insert(0, 1); 
	general.push_back(8); 
	general.printH(general); 
	general.printT(general);
}