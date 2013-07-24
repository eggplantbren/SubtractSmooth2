#ifndef _Data_
#define _Data_

#include <vector>

class Data
{
	private:


	public:
		Data();
		void load(const char* filename);

	private:
		static Data instance;
	public:
		static Data& get_instance() { return instance; }

};

#endif

