<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Account Registration and Login System - README</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            background-color: #f4f4f4;
            padding: 20px;
        }
        h1, h2 {
            color: #333;
        }
        code {
            background-color: #eee;
            padding: 2px 6px;
            border-radius: 4px;
        }
        .section {
            background: white;
            border-radius: 8px;
            padding: 15px;
            margin-bottom: 20px;
            box-shadow: 0 0 5px rgba(0,0,0,0.1);
        }
    </style>
</head>
<body>

  <h1>📘 Account Registration and Login System</h1>

  <div class="section">
        <h2>Overview</h2>
        <p>This C++ program provides a simple terminal-based system for registering user accounts and logging in. It stores user data (username, password, email) in a local file named <code>data.txt</code>.</p>
    </div>

  <div class="section">
        <h2>📂 File Used</h2>
        <ul>
            <li><code>data.txt</code>: Stores user credentials in the format <code>username,password,email</code> (comma-separated).</li>
        </ul>
    </div>

  <div class="section">
        <h2>🧩 Main Components</h2>

  <h3>1. <code>Registering</code> Class</h3>
        <ul>
            <li><code>setAccount()</code>: Sets the user's username, password, and email.</li>
            <li><code>UnqiueUsername()</code>: Checks if the entered username already exists in <code>data.txt</code>.</li>
            <li><code>SaveAccountData()</code>: Appends the new user’s credentials to the file if the username is unique.</li>
        </ul>

  <h3>2. <code>LogingIn</code> Class</h3>
        <ul>
            <li><code>setCredentials()</code>: Sets the username and password entered by the user.</li>
            <li><code>checkLoginCredentials()</code>: Reads <code>data.txt</code> and checks if the credentials match an existing record. Only the first line is checked due to a logic issue (see note below).</li>
        </ul>
    </div>

  <div class="section">
        <h2>🎮 Menu System</h2>
        <p>The user is presented with a menu to:</p>
        <ul>
            <li><strong>1. Register</strong>: Prompts for a username, password, and email. Checks if the username is unique and saves the account.</li>
            <li><strong>2. Login</strong>: Prompts for username and password and verifies them against the stored file.</li>
            <li><strong>3. Quit Program</strong>: Exits the program.</li>
        </ul>
    </div>

  <div class="section">
        <h2>⚠️ Notes and Issues</h2>
        <ul>
            <li><strong>Bug in Login:</strong> The <code>checkLoginCredentials()</code> function only reads the first line of <code>data.txt</code>. To properly check all stored users, a loop should be implemented.</li>
            <li><strong>Typo in Naming:</strong> <code>UnqiueUsername</code> is misspelled (should be <code>UniqueUsername</code>).</li>
            <li><strong>Password Field:</strong> In <code>LogingIn::setCredentials</code>, the password is incorrectly set as <code>this->password = username;</code>. It should be <code>this->password = password;</code>.</li>
        </ul>
    </div>

  <div class="section">
        <h2>✅ How to Use</h2>
        <ol>
            <li>Compile the program using a C++ compiler (e.g., <code>g++ main.cpp -o program</code>).</li>
            <li>Run the executable (e.g., <code>./program</code>).</li>
            <li>Select options from the menu to register or log in.</li>
        </ol>
  </div>

  <div class="section">
      <h2>📌 Example Data Format (in data.txt)</h2>
      <pre>
john123,password123,john@email.com
janeDoe,securePass,jane@domain.com
        </pre>
    </div>

</body>
</html>
