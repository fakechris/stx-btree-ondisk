// win32test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <stdlib.h>
#include <winsock2.h>

#include <stx/btree>

const int PAGE_SIZE = 1024;

enum ePageType
{
	root_page,
	inner_page,
	leaf_page,
	data_page
};

struct common_page_header
{	
	bool is_deleted;
	ePageType page_type;	
	unsigned char page_size;	
	unsigned char reserved;

	unsigned short  level;
	unsigned short  slotuse;

	unsigned long page_id;	
};

struct root_page_header : public common_page_header
{
	//unsigned long version;
	//unsigned long max_page;
};

struct inner_page_header : public common_page_header
{	
};

struct leaf_page_header : public common_page_header
{
	unsigned long prev_page_id;
	unsigned long next_page_id;
};

template <typename _Key, typename _Data>
struct btree_disk_traits
{
	static const bool   selfverify = false;
	static const bool   debug = false;
	static const int    leafslots = (PAGE_SIZE-sizeof(leaf_page_header)) / (sizeof(_Key) + sizeof(_Data));
	static const int    innerslots = (PAGE_SIZE-sizeof(inner_page_header)) / (sizeof(_Key) + sizeof(void*));
};

void test1()
{
	typedef stx::btree<unsigned long, unsigned long, 
		std::pair<unsigned long, unsigned long>, 
		std::less<unsigned long>,
		btree_disk_traits<unsigned long, unsigned long>,
		true> disk_btree;

	disk_btree db;

	db.insert(std::pair<unsigned long, unsigned long>(1,2));
	db.insert(std::pair<unsigned long, unsigned long>(2,2));
}

int _tmain(int argc, _TCHAR* argv[])
{
	test1();
	return 0;
}

