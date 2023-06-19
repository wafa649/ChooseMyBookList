# Synopsis:

This C project utilizes SQLite3 to enable users to create a personalized list of their favorite books, selecting from a collection of the most renowned books in history.

# Details:

The program automatically saves the list of favorite books, allowing easy access during subsequent program sessions.

The list of favorite books is stored in a file named "book_list.txt," which is created alongside the program.
<p align="center">
<img src="book_list.png" alt="drawing" width="400"/>
</p>

The SQLite database is stored in a file named "listedeslivres.db," located next to the program.
<p align="center">
<img src="listedeslivres.png" alt="drawing" width="370"/>
</p>


# Commands:

show: This command displays a comprehensive list of the most famous books in history. Each book is identified by an ID, and includes a title and the name of the author.
<p align="center">
<img src="showcommand.png" alt="drawing" width="400"/>
</p>

id: This command enables users to select a book from the list and add it to their list of favorite books.
<p align="center">
<img src="idcommand.png" alt="drawing" width="400"/>
</p>

liste: This command shows the names of the books in the favorite list.
<p align="center">
<img src="" alt="drawing" width="400"/>
</p>

close: This command terminates the program.
<p align="center">
<img src="closecommand.png" alt="drawing" width="500"/>
</p>
