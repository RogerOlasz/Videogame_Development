#ifndef __DList_H__
#define __DList_H__

#include <iostream>
#include <assert.h>
#include "Swap.h"

template<class TYPE>
struct  DNode
{
	TYPE data;
	DNode<TYPE>* next;
	DNode<TYPE>* previous;
};

template<class TYPE>
class DList {

private:
	DNode<TYPE>* start;

public:
	DList<TYPE>()
	{
		start = NULL;
	}

	unsigned int Count() const
	{
		unsigned int Counter = 0;
		DNode<TYPE>* tmp = start;

		while (tmp != NULL)
		{
			tmp = tmp->next;
			Counter++;
		}

		return Counter;
	}

	const DList<TYPE>& operator+= (DList &list_to_Add)
	{
		DNode<TYPE> *item_to_Add = list_to_Add.getFirst();

		while (item_to_Add != NULL)
		{
			Add(item_to_Add->data);
			item_to_Add = item_to_Add->next;
		}

		return (*this);
	}

	void AddList(unsigned int index, const DList<TYPE>& list)
	{
		DNode<TYPE> *my_list = getNodeAtPos(index);
		DNode<TYPE> *other_list = list.start;


		while (other_list != NULL)
		{
			DNode<TYPE> *new_node = new DNode<TYPE>(other_list->data);

			new_node->next = my_list->next;

			if (new_node->next != NULL)
			{
				new_node->next->previous = new_node;
			}

			new_node->previous = my_list;

			if (new_node->previous != NULL)
			{
				new_node->previous->next = new_node;
			}
			else
			{
				start = new_node;
			}

			my_list = new_node;
			other list = other_list->next;
		}
	}

	void Add(TYPE new_data)
	{
		DNode<TYPE>* new_node = new DNode<TYPE>;
		new_node->data = new_data;
		new_node->next = NULL;

		if (start != NULL)
		{
			DNode<TYPE>* tmp = start;

			while (tmp->next != NULL)
			{
				tmp = tmp->next;
			}
				
			tmp->next = new_node;
			new_node->previous = tmp;
		}

		else
		{
			new_node->previous = NULL;
			start = new_node;
		}
	}

	bool At(unsigned int index, TYPE &new_data) const
	{
		bool ret = false;
		DNode<TYPE>* searching_node = start;

		for (unsigned int i = 0; i < index - 1 && searching_node != NULL; ++i)
		{
			searching_node = searching_node->next;
		}		

		if (searching_node != NULL)
		{
			ret = true;
			new_data = searching_node->data;
		}

		return ret;
	}

	bool Del(DNode<TYPE>* delete_node)
	{
		if (start != NULL && delete_node != NULL)
		{
			if (start != delete_node)
			{
				DNode<TYPE>* tmp = start;

				while (tmp->next != delete_node)
				{
					tmp = tmp->next;
					if (tmp->next == NULL)
					{
						return false;
					}	
				}

				tmp->next = delete_node->next;

				if (delete_node->next != NULL)
				{
					delete_node->next->previous = tmp;
				}
				else
				{
					tmp->next = NULL;
				}
			}
			else
			{
				if (delete_node->next != NULL)
				{
					start = delete_node->next;
					delete_node->next->previous = NULL;
				}
				else
				{
					start = NULL;
				}
					
			}
			delete delete_node;
			return true;
		}
		return false;
	}

	bool DelList() 
	{
		if (start != NULL)
		{
			while (start->next != NULL)
			{
				DNode<TYPE>* node_to_delete = start;
				start = start->next;
				delete node_to_delete;
			}
			start = NULL;
			return true;
		}
		return false;
	}

	bool IsOnList(const DNode<TYPE> *node_to_check) const
	{
		if (start != NULL && node_to_check != NULL)
		{
			DNode<TYPE> *item = start;
			while (item != NULL)
			{
				if (item->data == node_to_check->data)
				{
					return true;
				}
					
				item = item->next;
			}
		}
		return false;
	}


	int Find(const TYPE& data)
	{
		DNode<TYPE>* tmp = start;
		unsigned int index = 0;

		while (tmp != NULL)
		{
			if (tmp->data == data)
			{
				return (index);
			}

			++index;
			tmp = tmp->next;
		}
		return (-1); //Doesn't exist nodes
	}

	bool Insert(const DList &inserted_list, unsigned int position)
	{
		if (position < Count())
		{
			DList<TYPE> tmp_list;
			for (unsigned int i = position; i < Count(); i++)
			{
				tmp_list.Add(getNodeAtPos(i)->data);
				del(getNodeAtPos(i));
			}

			for (unsigned int i = 0; i < inserted_list.Count(); i++)
			{
				Add(inserted_list.getNodeAtPos(i)->data);
			}

			for (unsigned int i = 0; i < tmp_list.Count(); i++)
			{
				Add(tmp_list.getNodeAtPos(i)->data);
			}
			return true;
		}
		return false;
	}
	//Ordenar de mes petit a mes gran (Ordena per data)
	unsigned int Sort_copy()
	{
		unsigned int Counter = 0;
		for (unsigned int i = 0; i < Count() - 1; i++)
		{
			for (unsigned int j = i + 1; j < Count(); j++)
			{
				Counter++;
				if (getNodeAtPos(i)->data > getNodeAtPos(j)->data)
				{
					Swap(getNodeAtPos(i)->data, getNodeAtPos(j)->data);
				}
					
			}
		}
		return Counter;
	}
	//Ordenar de mes petit a mes gran (Ordena per referencies)
	unsigned int Sort_reference()
	{
		unsigned int Counter = 0;
		DNode<TYPE> *first_node;
		DNode<TYPE> *second_node;

		for (unsigned int i = 0; i < Count() - 1; i++)
		{
			first_node = getNodeAtPos(i);
			for (unsigned int j = i + 1; j < Count(); j++)
			{
				second_node = getNodeAtPos(j);
				Counter++;

				if (first_node->data > second_node->data)
				{

					if (first_node->previous = NULL)
					{
						first_node->previous = second_node->previous;
						second_node->previous = NULL;
					}
					else
					{
						Swap(first_node->previous->next, second_node->previous->next);
					}	

					if (second_node->next = NULL)
					{
						second_node->next = first_node->next;
						first_node->next = NULL;
					}
					else
					{
						Swap(first_node->next->previous, second_node->next->previous);
					}

					Swap(first_node->next, second_node->next);
					Swap(first_node->previous, second_node->previous);

				}
			}
		}
		return Counter;
	}

	DNode<TYPE> *getFirst() const
	{
		return start;
	}

	DNode<TYPE> *getLast() const
	{
		if (start != NULL)
		{
			DNode<TYPE>* tmp = start;
			while (tmp->next != NULL)
			{
				tmp = tmp->next;
			}		
			return tmp;
		}
		return NULL;
	}

	DNode<TYPE>* getNodeAtPos(unsigned int position) const
		{
			if (start != NULL && position < Count())
			{
				unsigned int position_Counter = 0;
				DNode<TYPE>* tmp = start;

				while (position_Counter != position)
				{
					tmp = tmp->next;
					position_Counter++;
				}
				return tmp;
			}
			return NULL;
		}

	TYPE& operator  [](const unsigned int index)
	{
		long pos;
		DNode<TYPE>* item;
		pos = 0;
		item = start;

		while (item != NULL)
		{
			if (pos == index)
			{
				break;
			}
			++pos;
			item = item->next;
		}
		return(item->data);
	}

	//TO DEBUG
	void Info() const
	{
		if (start != NULL) 
		{
			DNode<TYPE>* tmp = start;
			unsigned int node_num = 1;

			while (tmp != NULL)
			{
				printf("%s %d: %s %d | %s %p | %s %p | %s %p\n",
					"Number", node_num,
					"Data", tmp->data,
					"Node", tmp,
					"Next", tmp->next,
					"Previous", tmp->previous);
				tmp = tmp->next;
				node_num++;
			}
			printf("%s\n", "--------------------------------");
		}
		else
		{
			printf("%s\n", "Empty Double Linked List");
		}		
	}

};

#endif //__DList_H__