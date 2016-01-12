void Singly_Linked_List::append ( data d )
{
	if (head == NULL)
	{
		head = new (nothrow) listcell;
		if (!head) { //ERROR MESSAGE }
		head->x = d;
		head->next = NULL;	//listcell class automatically sets next to null, but repeated anyways
	}
	else
	{
		listcell * cursor;
		cursor = head;

		while(cursor->next)
		{
			cursor = cursor->next;
		}

		cursor->next = new (nothrow) listcell;
		cursor = cursor->next;
		cursor->x = d;
		cursor->next = NULL;
	}
}
