#ifndef ARRAY3D_H
#define ARRAY3D_H


class array3d
{
	private:
		int m, n, p;
		char *** dataTable;
		void init();
	public:
		array3d();
		~array3d();
		bool read (char * fname);
		void get_sizes (int & m, int & n, int & p);
		char get_zmap_value (int x, int y);
};

#endif
