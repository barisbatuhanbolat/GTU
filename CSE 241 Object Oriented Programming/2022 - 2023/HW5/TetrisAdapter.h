#ifndef TETRISADAPTER_H
#define TETRISADAPTER_H
#include "AbstractTetris.h"
#include <unistd.h>
#include <list>

namespace HW5{
    template<class T,class C>
    class TetrisAdapter : public AbstractTetris{
        public:
            TetrisAdapter(){};
            TetrisAdapter(int heightT,int  widthT);
            //-------------------------------------------------
            virtual ~TetrisAdapter() =  default;
            virtual void readFromFile() override;
            virtual void writeToFile() const override;
            virtual void draw() const override;
            virtual void operator+=(Tetromino & newT) override;
            virtual void animate() override;
            virtual bool isFilled(const int &newX, const int &newY) const override;
            virtual void move(const int &newX, const int &newY) override;
        private:

            T board;
            T board_cpy;
            T tetro;
    };
    //Templated constructor
    template<class T,class C>
    TetrisAdapter<T,C>::TetrisAdapter(int heightT,int  widthT) : AbstractTetris(heightT,widthT){
        //Check existing file
        char key;
        string filename = "Program.txt";
        ifstream f(filename.c_str());
        bool n = f.good();
        f.close();
        //If there is a file that contains board ask user for uploading
        //Declaring templated variables with iterator
        if(n == true){
            cout << "A saved file for the object was found. Do you want to upload(Y/N) : ";
            cin >> key;
            if(key == 'Y' || key == 'y'){
                readFromFile();
            }
            else if(key == 'N' || key == 'n'){
                width = widthT;
                height = heightT;
                board.resize(heightT,C(widthT));
                for(auto i1=board.begin();i1!=board.end();i1++)
                {
                    C& list2=*i1; 
                    for(auto j1=list2.begin();j1!=list2.end();j1++)
                    {
                        if ((i1 == board.begin())||(j1 == list2.begin()) || (j1 == --(--(list2.end()))) || (i1 == --(--(board.end())))) {
                            *j1 = 2;
                            
                        } 
                        else {
                            *j1 = 0;
                        }
                    }
                }                
            }
        }
        else{
            board.resize(heightT,C(widthT));
            for(auto i1=board.begin();i1!=board.end();i1++)
            {
                C& list2=*i1; 
                for(auto j1=list2.begin();j1!=list2.end();j1++)
                {
                    if ((i1 == board.begin())||(j1 == list2.begin()) || (j1 == --(--(list2.end()))) || (i1 == --(--(board.end())))) {
                        *j1 = 2;
                        
                    } 
                    else {
                        *j1 = 0;
                    }
                }
            }
        }
        board_cpy.resize(heightT,C(widthT));
        tetro.resize(4,C(4));


        board_cpy = board;
        for (auto i1=tetro.begin(); i1 < tetro.end(); i1++) {
            C& list2 = *i1;
            for (auto j1 = list2.begin(); j1 < list2.end(); j1++) {
                *j1 = 0;
            }
        }
        isGameOver = false;
    }
    //Templated draw function. This function prints the board 
    template<class T,class C>
    void TetrisAdapter<T,C>::draw() const{
        usleep(50000);
        cout << "\x1B[2J\x1B[H";
        for(auto i1=board.begin();i1!=board.end();i1++)
        {
            C list2=*i1;
            for(auto j1=list2.begin();j1!=list2.end();j1++)
            {
                if(*j1 == 2)
                    cout << '*';
                else if(*j1  == 0)
                    cout << ' ';
                else if(*j1 == 1)
                    cout << 'X';
                else if(*j1 == 3)
                    cout << 'K';                    
            }
            cout << endl;
        }
    }
    //Templated move function
	//This function moves the tetromino
	template<class T,class C>
    void TetrisAdapter<T,C>::move(const int &newX, const int &newY) {
		//Remove block
        int dif;
        auto i3 = board.begin()+y;
        auto i4 = (*i3).begin();
        i4 = i4 + x;
        for ( const auto &row : tetro)
        {
            for ( const auto &k: row )
            {   
                dif = *i4 - k;
                *i4 = dif;
                i4 = i4 + 1;
                
            }
            ++i3;
            i4 = (*i3).begin() +x;
        }        
		//Update coordinates
		x = newX;
		y = newY;
        //Adding block to updated position
        int sum;
        auto i1 = board.begin()+y;
        auto i2 = (*i1).begin();
        i2 = i2 + x;
        for ( const auto &row : tetro)
        {
            for ( const auto &k: row )
            {   
                sum = *i2+ k;
                *i2 = sum;
                i2 = i2 + 1;
                
            }
            ++i1;
            i2 = (*i1).begin() +x;
        }

	}
    //Templated check fillness function
    //This function checks the fullness of the next block
    template<class T,class C>
	bool TetrisAdapter<T,C>::isFilled(const int &newX, const int &newY) const {

        for(auto i1=board_cpy.begin(),i2 = tetro.begin();i2!=tetro.end();i1++,i2++)
        {
            C list2=*i1;
            C list3 = *i2;
            C list4=*(i1+newY);

            for(auto j1=list2.begin(),j3 = list4.begin(),j2 = list3.begin()+1;j2!=list3.end()+1;j1++,j2++,j3++)
            {

                if((*j2 != 0) && (*(j3+newX+1) != 0)){
                    return true;
                }
            }
        }
		return false;
	}
    //+= operator overload for adding tetromino to the board
    template<class T,class C>
    void TetrisAdapter<T,C>::operator+=(Tetromino & newT){
        x = width/2-1;
		y = 0;
        m = newT;
        //Receiving tetrominos shape to the 'tetro' variable
        auto i0 = tetro.begin();
        auto i01 = (*i0).begin();

        for ( const auto &row : m.getTetro())
        {
            for ( const auto &x: row )
            {
                *i01 = x;
                i01 = i01 + 1;
            }
            ++i0;
            i01 = (*i0).begin();
            
        }

        //Adding tetro to board
        auto i1 = board.begin();
        auto i2 = (*i1).begin();
        i2 = i2 + x;
        for ( const auto &row : tetro)
        {
            for ( const auto &col: row )
            {
                *i2 = col;
                i2 = i2 + 1;
            }
            ++i1;
            i2 = (*i1).begin() + x;
            
        }
        //Controlling board for GameOver conditions
        for(auto i1=board.begin()+1;i1!=board.end()-3;i1++)
        {
            C& list2=*i1;
            for(auto j1=list2.begin()+1;j1!=list2.end()-2;j1++)
            {
                if((*j1 > 1)){
                    isGameOver = true;
                }   
            }
        }
    } 
    //This function moves and rotates the tetromino tetro according to the user's choice.
    template<class T,class C>
    void TetrisAdapter<T,C>::animate() {
        try{
            //Writing board to the file when exiting
            if(isGameOver == true){
                cout << "\e[0;31m----------GAME OVER----------\e[0m" << endl;
                cout << "Last Move : " << lastMove() << endl;
                cout << "Total Moves : " << numberOfMoves() << endl;
                cout << "Program saved to the file named \"Program.txt\"" << endl;
                writeToFile();
                exit(0);
            }
            draw();
            //Asking user for rotation and horizontaly movement
            int choice,rCount = 0,choice2,mCount = 0;
            cout << "Enter Rotation" << endl;
            cout << "\t0 - None" << endl;
            cout << "\t1 - Left" << endl;
            cout << "\t2 - Right" << endl;
            cout << "Choice : ";
            while((!(cin>>choice)) || !(choice==1 || choice==2 || choice == 0)){
                cout << "Wrong choice: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cout << "Enter Rotation Count : ";
            while((!(cin>>rCount)) || (rCount<0)){
                cout << "Wrong choice: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cout << "Enter Move Direction" << endl;
            cout << "\t0 - None" << endl;
            cout << "\t1 - Left" << endl;
            cout << "\t2 - Right" << endl;
            cout << "Choice : ";
            while((!(cin>>choice2)) || !(choice2==1 || choice2==2 || choice2 == 0)){
                cout << "Wrong choice: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cout << "Enter Move Direction Count : ";
            while((!(cin>>mCount)) || (mCount<0) || (mCount + abs(x) >= width)){
                cout << "Invalid count! Try again: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            T temp(4,C(4));
            temp = tetro;
            //Rotating by choice		
            for(int i=0;i<rCount;i++){
                auto i0 = tetro.begin();
                auto i01 = (*i0).begin();

                for ( const auto &row : m.rotate(choice))
                {
                    for ( const auto &x: row )
                    {
                        *i01 = x;
                        i01 = i01 + 1;
                    }
                    ++i0;
                    i01 = (*i0).begin();
                    
                }
            }
            //If place is filled return the old version
            if (isFilled(x, y)) {
                tetro = temp;
            }

            for(auto i1=board.begin(),i2 = temp.begin();i2!=temp.end();i1++,i2++)
            {
                C& list2=*i1;
                C& list3 = *i2;
                for(auto j1=list2.begin(),j2 = list3.begin()+1;j2!=list3.end()+1;j1++,j2++)
                {
                    
                    i1 = i1 + y;
                    *(j1+x) = 0;
                }
            }
            auto i1 = board.begin()+y;
            auto i2 = (*i1).begin();
            i2 = i2 + x;
            for ( const auto &row : tetro)
            {
                for ( const auto &k: row )
                {
                    *i2 = k;
                    i2 = i2 + 1;
                    
                }
                ++i1;
                i2 = (*i1).begin() +x;
            }
            //Move on top horizontaly
            if(choice2 == 1){
                if (!isFilled(x-mCount, y))
                    move(x-mCount, y);
            }
            else if(choice2 == 2){
                if (!isFilled(x+mCount, y))
                    move(x+mCount, y);
            }
            xTotal+=mCount;
            lastM = mCount;
            while (isGameOver == false) {
                //Move downward according the fullness
                if (isFilled(x, y + 1) == false) {
                    move(x, y + 1);
                    lastM = 1;
				    ++yTotal;
                }
                else {
                    board_cpy = board;
                    draw();
                    return;
                }
                draw();
            }
        }
        catch(const std::exception& e){
            cout << e.what() << endl;
        }
    }
    //Templated file reading function
    //This function reads the file and puts the board to the templated board variable
    template<class T,class C>
    void TetrisAdapter<T,C>::readFromFile(){
		try{
			ifstream in("Program.txt");
			if (in.fail()) throw "File.txt";
			vector<string> temp1;
			string id;
			while (getline(in,id))
			{
				temp1.push_back(id);
			}
			height =temp1.size();
			width = temp1[0].size();
			board.resize(height,C(width));

            auto i1 = board.begin();
            auto i2 = (*i1).begin();
			for(int i = 0;i<temp1.size();i++){
				for(int j = 0;j<temp1[i].size();j++){
						if(temp1[i][j] == '*')
							*i2 = 2;
						else if(temp1[i][j] == 'X')
							*i2 = 1;
						else if(temp1[i][j] == ' ')
							*i2 = 0;
                        ++i2;
				}
                ++i1;
                i2 = (*i1).begin();
			}
			in.close();
		}
		catch(string e){
            cout << e << " was not successfully opened.\n Please check that the file currently exists." << endl;
            exit(1);
		}
	}
    //Templated file writing function
    //This function writes the templated board to the file
    template<class T,class C>
    void TetrisAdapter<T,C>::writeToFile() const {
        try{
            ofstream Out("Program.txt");
            if (Out.fail()) throw "File.txt";
            auto row_it = board.begin();
            auto row_end = board.end();
            
            for ( ; row_it != row_end; ++row_it )
            {
                
                auto col_it = row_it->begin();
                auto col_end = row_it->end();
                
                for ( ; col_it != col_end; ++col_it ){
                        if(*col_it == 2)
                            Out << '*';
                        else if(*col_it == 1)
                            Out << 'X';
                        else if(*col_it == 0)
                            Out << ' ';
                }
                Out << '\n';
            }
            Out.close();
        }
		catch(string e){
            cout << e << " was not successfully opened.\n Please check that the file currently exists." << endl;
            exit(1);
		}
	}
}
#endif