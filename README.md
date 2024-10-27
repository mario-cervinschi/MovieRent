# MovieRent - About the application
Movie Rent App is made in C++ using QT GUI. This app has been made during the OOP course, learning its concepts. I have expanded my skills regarding the memory management (memory leaks, dangling pointers, smart pointers etc.) and using concepts such as iterators, templates etc. and creating them from scratch (e.g. similar vector from STL).
I also had the opportunity to learn how to use the signals and create a basic GUI using QT.
### The functionalities

This application lets you add, update, delete a movie and filter or sort them from the repository. Additional options are available, such as:
- Undo last operation
- Generate a report
- Add to basket

## The GUI 
![gui](https://github.com/user-attachments/assets/c353c883-a1c8-4bab-a2a4-4d90f616b53d)
- To **add a movie**, you simply write down its title, genre, main actor and year of release and press "Adauga film".
- To **update a movie** you can either select a movie to update or write down its title and the other data you want to update in the fields and press "Modifica film".
- To **delete a move** you can either select a movie to delete or write down its title and press "Sterge film".

### Generate a report
This option basically lets you know how many movies have been released in a certain year.

![report](https://github.com/user-attachments/assets/13af06c7-5751-41c0-84a9-4d18379a6124)

The report is in the pop-up shown above.

### Filter movies
There are two options. You can either filter a movie by its title or its release year.
You simply put the data in the text-field and press the button to filter by your preference.

![filter1](https://github.com/user-attachments/assets/7ba924a3-9fb6-4e3a-934f-e95589df8b60)
![filter2](https://github.com/user-attachments/assets/7e1de392-3ec5-4777-ac22-90a8d08c5105)

Here you can see all the movies from the year "2024".

### The basket
Pressing the "Deschide cos" button will open a window (or more if you'd like).

![basket](https://github.com/user-attachments/assets/ab3f3284-9d0e-4cb7-b2da-2497ff700183)

Here you can Add Random Movies ("Adauga random") to the basket, empty the basket ("Goleste lista") and export the basket to a file. You can also click on a movie from the main window and add it to the basket by pressing "Adauga la rent".
*Note: multiple baskets opened __will show the same__ contents. this has been made using an "Observer".*

![baskets](https://github.com/user-attachments/assets/56ae0dff-2b83-40f8-be7e-e97b3ced8506)
