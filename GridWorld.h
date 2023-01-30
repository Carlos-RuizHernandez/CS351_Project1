
#ifndef _GRID_WORLD_H
#define _GRID_WORLD_H

#include <vector>
#include <iostream>

using std::vector;


class GridWorld {

  private:
    // private stuff goes here!
    //   typedefs
    //   data members
    //   private helper functions
    //   etc.

    // structs that encapsulate the world

    // person struct acts as "nodes"
    struct person{
      int status; // whether person is dead or alive (0 if dead/1 if alive)
      int ID; // person ID
      struct person* next; // doubly linked list
      struct person* prev; // doubly linked list allows for easy access to neighbors in district
      int r;
      int c;
    };

    // all elements in world grid consist of 1 district with multiple people
    struct district {
      int pop;
      struct person* head; //most senior
      struct person* tail; //least senior
    };

    // encapsulates current state of the world
    struct world {
      int pop; //number of people currently living (not dead)
      district[][] grid; // district grid
      person* reuse; // dead people available for reuse, oldest is pointed to
      vector<person> bucket; // contains all allocated people for easy access
      int births; // total amount of allocated people (size of bucket)
      int available_IDs; // # of IDs in reuse list (size of reuse)
      int numrows; // easy access for num_rows() function
      int numcols; // easy access for num_cols() function
    };

    // TODO: Queue functions (dequeue, enqueue, size)
    // Head will be most senior, tail will be most junior

  public:
    /**
    * constructor:  initializes a "world" with nrows and
    *    ncols (nrows*ncols districtcs) in which all 
    *    districtricts are empty (a wasteland!).
    */
    // Sami
    GridWorld(unsigned nrows, unsigned ncols)   {
        world planetEarth = new world;
        planetEarth.pop = 0;
        planetEarth.grid =

    }
    ~GridWorld(){
      // your destructor code here.
    }

    /*
     * function: birth
     * description:  if row/col is valid, a new person is created
     *   with an ID according to rules in handout.  New person is
     *   placed in district (row, col)
     *
     * return:  indicates success/failure
     */
     // Sami
    bool birth(int row, int col, int &id){
      return false;
    }

    /*
     * function: death 
     * description:  if given person is alive, person is killed and
     *   data structures updated to reflect this change.
     *
     * return:  indicates success/failure
     */
    bool death(int personID){

      return false;
    }


    /*
     * function: whereis
     * description:  if given person is alive, his/her current residence
     *   is reported via reference parameters row and col.
     *
     * return:  indicates success/failure
     */
    bool whereis(int id, int &row, int &col)const{
      return false;
    }

    /*
     * function: move
     * description:  if given person is alive, and specified target-row
     *   and column are valid, person is moved to specified district and
     *   data structures updated accordingly.
     *
     * return:  indicates success/failure
     *
     * comment/note:  the specified person becomes the 'newest' member
     *   of target district (least seniority) --  see requirements of members().
     */
    bool move(int id, int targetRow, int targetCol){
      return false;
    }

    std::vector<int> * members(int row, int col)const{

      return nullptr;
    }

    /*
     * function: population
     * description:  returns the current (living) population of the world.
     */
    int population()const{
      return 0;
    }
    
    /*
     * function: population(int,int)
     * description:  returns the current (living) population of specified
     *   district.  If district does not exist, zero is returned
     */
    int population(int row, int col)const{
      return 0;
    }

    /*
     * function: num_rows
     * description:  returns number of rows in world
     */
    int num_rows()const {
      return 0;
    }

    /*
     * function: num_cols
     * description:  returns number of columns in world
     */
    int num_cols()const {
      return 0;
    }



};

#endif
