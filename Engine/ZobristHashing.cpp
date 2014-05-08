
#include "ZobristHashing.h"

using namespace stdext;

namespace engine{

	void ZobristHashing::init_zobrist()
	{
		srand((unsigned)time(NULL));
	
		for(int i=0;i<16;i++)
		{
			for(int j=0; j<400; j++)
			{
				table[i][j] = rand()%1000;
			}
		}


	}

	void ZobristHashing::board_hash()
	{







	}

	int ZobristHashing::hash(Board a) 
	{
		int h =0;

		for(int i=0; i<20;i++)
		{
				for(int k=0; k<20; k++)
			{
				Cell<int>* j=a.GetAbsoluteCellAt(Vector2D(i,k));
				int value = (int)j->GetPosition().X() + (int)j->GetPosition().Y()*20;

				if(j->GetData() != 2)
				{
					h=h^table[j->GetData()][value];

				}

			}
		}
		return h;
		

	}



}
