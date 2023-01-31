
#ifndef _GRID_WORLD_H
#define _GRID_WORLD_H

#include <vector>
#include <iostream>

using std::vector;


class GridWorld {

  private:
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
      vector<vector<district*>> grid; // district grid
      person* reuseHead; // oldest dead person
      person* reuseTail; // newest dead person
      vector<person*> bucket; // contains all allocated people for easy access
      int births; // total amount of allocated people (size of bucket)
      int available_IDs; // # of IDs in reuse list (size of reuse)
      int numrows; // easy access for num_rows() function
      int numcols; // easy access for num_cols() function
    };

    world* planetEarth;

    // TODO: Queue functions (dequeue, enqueue, size)
    // Head will be most senior, tail will be most junior

    //
    // addToDistrict()
    // adds person to a given district, 
    //
    void addToDistrict(world*& planet, district*& d, person*& p, int row, int col) {
      // empty district
      if (d->pop == 0) {
          // add person to district list
          d->head = p;
          d->tail = p;
          p->prev = NULL;
        } else {  // non-empty district
          d->tail->next = p;
          p->prev = d->tail;
          d->tail = p;
        }
        // assign/update values for district/person/world
        p->next = NULL;
        p->status = 1;
        p->r = row;
        p->c = col;
        // update populations accordingly
        d->pop++;
        planet->pop++;
    }

    //
    // removeFromDistrict()
    // removes person from a given district
    //
    void removeFromDistrict(world*& planet, district*& d, person*& p) {
      // case person is head of the queue
      if (p == d->head) {
        d->head = d->head->next;
        d->head->prev = NULL;
      } else if (p == d->tail) {
      // case person is at tail of the queue
        d->tail = d->tail->prev;
        d->tail->next = NULL;
      } else {
      // case person is in middle of queue
        person* previous = &*p->prev;
        person* next = &*p->next;
        previous->next = next;
        next->prev = previous;
      }

      // add person to reuse queue
      if (planet->reuseHead == NULL) {
        planet->reuseHead = p;
        planet->reuseTail = p;
        p->next = NULL;
        p->prev = NULL;
      } else {
        planet->reuseTail->next = p;
        p->prev = planet->reuseTail;
        p->next = NULL;
        planet->reuseTail = p;
      }
      planet->available_IDs++;
      planet->pop--;
      d->pop--;
      // adjust person values to fit a dead person
      p->status = 0;
      p->r = -1;
      p->c = -1;
    }

    //
    // birthOrAdopt()
    // checks if a person ID can be reassigned or if a new person must be created
    //
    person* birthOrAdopt(world*& planet, int row, int col) {
      person* newPerson;

      // resusable IDs are available
      if (planet->available_IDs > 0) {
        // move oldest dead person over
        newPerson = planet->reuseHead;
        planet->reuseHead = planet->reuseHead->next;
        planet->available_IDs--;
      } else { // no resuable people
        // create new person and add to bucket
        newPerson = new person;
        planet->bucket.push_back(newPerson);
        newPerson->ID = planet->births;
        planet->births++;
      }

      return newPerson;
    }

  public:
    /**
    * constructor:  initializes a "world" with nrows and
    *    ncols (nrows*ncols districts) in which all 
    *    districtricts are empty (a wasteland!).
    */
    // Sami
    GridWorld(unsigned nrows, unsigned ncols)   {
        planetEarth = new world;
        planetEarth->pop = 0;

        // Creates the district grid
        for (int x = 0; x < nrows; x++) {
          for (int y = 0; y < ncols; y++) {
            district* newD = new district;
            newD->pop = 0;
            newD->head = NULL;
            newD->tail = NULL;

            planetEarth->grid[x][y] = newD;
          }
        }

        // Intializing world instance variables
        planetEarth->reuseHead = NULL;
        planetEarth->reuseTail = NULL;
        planetEarth->births = 0;
        planetEarth->available_IDs = 0;
        planetEarth->numrows = nrows;
        planetEarth->numcols = ncols;
    }

    ~GridWorld(){
      for (int x = 0; x < planetEarth->numrows; x++) {
          for (int y = 0; y < planetEarth->numcols; y++) {
            delete[] planetEarth->grid[x][y];
          }
      }

      for (auto person : planetEarth->bucket) {
        delete[] person;
      }

      delete[] planetEarth;
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
      // new person and target district
      person* newPerson;
      district* targetDistrict;

      // check for valid row and column
      if (row < planetEarth->numrows && row >= 0 && col < planetEarth->numcols && col >= 0) {

        // assign valid district for readability
        targetDistrict = planetEarth->grid[row][col];

        // check if new person needs to be birthed or reassigned
        newPerson = birthOrAdopt(planetEarth, row, col);

        // add to target district
        addToDistrict(planetEarth, targetDistrict, newPerson, row, col);
        return true;

      } else {
        return false; //invalid row/col
      }
      
    }

    /*
     * function: death 
     * description:  if given person is alive, person is killed and
     *   data structures updated to reflect this change.
     *
     * return:  indicates success/failure
     */
    bool death(int personID){
      //check if person exists
      if (personID < planetEarth->births) {

        person* markedForDeath = planetEarth->bucket[personID];

        // check if person is alive
        if (markedForDeath->status == 1) {
          district* targetDistrict = planetEarth->grid[markedForDeath->r][markedForDeath->c];
          removeFromDistrict(planetEarth, targetDistrict, markedForDeath);
          return true;
        }
      }

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
      if (id < planetEarth->births) {
        if(planetEarth->bucket[id]->status == 1){
          row = planetEarth->bucket[id]->r;
          col = planetEarth->bucket[id]->c;
          return true;
        }
      }
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
      //check if person exists
      if (id < planetEarth->births) {

        person* moving = planetEarth->bucket[id];

        // check if person is alive
        if (moving->status == 1) {
          district* currentDistrict = planetEarth->grid[moving->r][moving->c];
          district* targetDistrict = planetEarth->grid[targetRow][targetCol];
          removeFromDistrict(planetEarth, currentDistrict, moving);
          addToDistrict(planetEarth, targetDistrict, moving, targetRow, targetCol);
          return true;
        }
      }

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
      return planetEarth->pop;
    }
    
    /*
     * function: population(int,int)
     * description:  returns the current (living) population of specified
     *   district.  If district does not exist, zero is returned
     */
    int population(int row, int col)const{
      return planetEarth->grid[row][col]->pop;
    }

    /*
     * function: num_rows
     * description:  returns number of rows in world
     */
    int num_rows()const {
      return planetEarth->numrows;
    }

    /*
     * function: num_cols
     * description:  returns number of columns in world
     */
    int num_cols()const {
      return planetEarth->numcols;
    }



};

#endif
