
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
    struct {
      int status; // whether person is dead or alive (0 if dead/1 if alive)
      int ID; // person ID
      struct person* next; // doubly linked list
      struct person* prev; // doubly linked list allows for easy access to neighbors in district
      int r;
      int c;
    } person;

    // all elements in world grid consist of 1 district with multiple people
    struct {
      int pop;
      struct person* head; //most senior
      struct person* tail; //least senior
    } district;

    // encapsulates current state of the world
    struct {
      int pop; //number of people currently living (not dead)
      vector<vector<district>> grid; // district grid
      person* reuse; // dead people available for reuse, oldest is pointed to
      vector<person> bucket; // contains all allocated people for easy access
      int births; // total amount of allocated people (size of bucket)
      int available_IDs; // # of IDs in reuse list (size of reuse)
      int numrows; // easy access for num_rows() function
      int numcols; // easy access for num_cols() function
    } world

    // TODO: Queue functions (dequeue, enqueue, size)
    // Head will be most senior, tail will be most junior

  public:
    /**
    * constructor:  initializes a "world" with nrows and
    *    ncols (nrows*ncols districtcs) in which all 
    *    districtricts are empty (a wasteland!).
    */
    GridWorld(unsigned nrows, unsigned ncols)   {

      // your constructor code here!
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

    // test hellooooo
    // Another comment

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
