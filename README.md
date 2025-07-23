<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">

</head>
<body>
  <h1>📘 Library Management System</h1>


  <div class="section">
    <h2>📄 Overview</h2>
    <p>This is a C++ console application that implements a functional Library Management System. It uses object-oriented programming principles and Standard Template Library (STL) containers such as <code>vector</code>, <code>map</code>, <code>list</code>, and <code>queue</code>. The system allows users to register, borrow and return books, and manage data using file input/output for persistence.</p>
  </div>

  <div class="section">
    <h2>🛠 Class Design</h2>
    <ul>
      <li><strong>Book</strong> – Represents a book with title, author, ISBN, availability, and request queue.</li>
      <li><strong>User</strong> – Manages a user’s name and a list of borrowed books.</li>
      <li><strong>Library</strong> – Handles the collection of books and users using vectors and maps. Core functionalities include:
        <ul>
          <li>add/remove/list books</li>
          <li>register users</li>
          <li>borrow/return books</li>
          <li>view borrowed books</li>
          <li>search/sort books</li>
          <li>load/save data from files</li>
        </ul>
      </li>
    </ul>
  </div>

  <div class="section">
    <h2>💾 File I/O Structure</h2>
    <p>Two files are used to persist data:</p>
    <ul>
      <li><strong>books.txt</strong> – Each book is stored using 4 lines:
        <ol>
          <li>Title</li>
          <li>Author</li>
          <li>ISBN</li>
          <li>Availability (1 = available, 0 = borrowed)</li>
        </ol>
      </li>
      <li><strong>users.txt</strong> – Each user is stored using:
        <ol>
          <li>Username</li>
          <li>Number of borrowed books</li>
          <li>One line per borrowed book (ISBN)</li>
        </ol>
      </li>
    </ul>
  </div>

  <div class="section">
    <h2>📋 Main Menu Options</h2>
    <p>The user is presented with the following options:</p>
    <ol>
      <li>Add Book</li>
      <li>Remove Book</li>
      <li>List All Books</li>
      <li>Register User</li>
      <li>Borrow Book</li>
      <li>Return Book</li>
      <li>View User Borrowed Books</li>
      <li>Search Book</li>
      <li>Sort Books</li>
      <li>Exit (saves data)</li>
    </ol>
  </div>

  <div class="section">
    <h2>🧰 STL Containers Used</h2>
    <ul>
      <li><strong>vector</strong> – Stores the collection of books</li>
      <li><strong>map</strong> – Maps usernames to user data</li>
      <li><strong>list</strong> – Manages the borrowed book list per user</li>
      <li><strong>queue</strong> – Handles waiting lists for unavailable books</li>
    </ul>
  </div>

  <div class="section">
    <h2>✅ Expected Behavior</h2>
    <ul>
      <li>Loads existing data from files on start.</li>
      <li>Handles duplicate usernames and invalid actions gracefully.</li>
      <li>Automatically assigns returned books to next waiting user.</li>
      <li>Persists all changes on exit.</li>
    </ul>
  </div>

  <div class="section">
    <h2>🧪 Sample Run</h2>
    <p>Here’s an example session:</p>
    <pre>
--- Library Menu ---
1. Add Book
...
Enter book title: 1984
Enter author: George Orwell
Enter ISBN: 9780451524935
Book added.

...
Enter user name: Alice
User registered.

...
Enter user name: Bob
User not found.

...
Enter user name: Bob
User registered.
Borrow Book -> Bob -> Book unavailable. Added to request queue.

...
Return Book -> Alice
Book auto-assigned to next requester: Bob
    </pre>
  </div>

  <div class="section">
    <h2>🚫 Error Handling Examples</h2>
    <ul>
      <li>Borrowing an unavailable book adds user to request queue.</li>
      <li>Trying to borrow the same book twice shows an error.</li>
      <li>Trying to register an existing user shows an error.</li>
      <li>Invalid ISBNs or usernames are handled gracefully.</li>
    </ul>
  </div>

  <div class="section">
    <h2>📎 Example Files</h2>
    <pre>
===== books.txt =====
The Great Gatsby
F. Scott Fitzgerald
9780743273565
1

1984
George Orwell
9780451524935
0

===== users.txt =====
Alice
0

Bob
1
9780451524935
    </pre>
  </div>

</body>
</html>
