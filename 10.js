//crud.js
const { MongoClient, ObjectId } = require("mongodb");
// Replace with your MongoDB Atlas connection string
const uri = "mongodb+srv://rabiya:12345@cluster9.1gbjnul.mongodb.net/?appName=Cluster9";
const client = new MongoClient(uri);
async function main() {
 try {
 await client.connect();
 console.log("Connected to MongoDB Atlas");
 const db = client.db("companyDB");
 const employees = db.collection("employees");
 // CREATE
 const insertResult = await employees.insertOne({
 name: "Alice Johnson",
 age: 30,
 department: "IT",
 salary: 85000
 });
 console.log(" Inserted:", insertResult.insertedId);
 // READ
 const allEmployees = await employees.find().toArray();
 console.log("All Employees:", allEmployees);
 // UPDATE
 const updateResult = await employees.updateOne(
 { name: "Alice Johnson" },
 { $set: { salary: 90000 } }
 );
 console.log(" Updated Count:", updateResult.modifiedCount);
 // DELETE
 const deleteResult = await employees.deleteOne({ name: "Alice Johnson" });
 console.log(" Deleted Count:", deleteResult.deletedCount);
 } catch (error) {
 console.error(" Error:", error);
 } finally {
 await client.close();
 console.log(" Connection closed");
 }
}
main();





//express.js
const express = require('express');
const session = require('express-session');
const app = express();
const PORT = 3000;

// Middleware to use sessions
app.use(session({
  secret: 'mySecret',
  resave: false,
  saveUninitialized: true
}));

// Home route
app.get('/', (req, res) => {
  if (req.session.views) {
    req.session.views++;
    res.send(`<h2>Welcome back!</h2>
      <p>Number of visits: ${req.session.views}</p>`);
  } else {
    req.session.views = 1;
    res.send('<h2>Hello! This is your first visit.</h2>');
  }
});

// Start server
app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
});
//Commands - node -v, npm install express express-session, node express.js

//app.js
import React, { useState } from "react";

function App() {
  const [show, setShow] = useState(true);

  return (
    <div style={{ fontFamily: "system-ui", padding: 20 }}>
      <h2>React Conditional Rendering</h2>

      {/* Conditional Rendering */}
      {show ? <p>Hello, welcome to React!</p> : <p>Goodbye!</p>}

      <button onClick={() => setShow(!show)}>
        {show ? "Hide Message" : "Show Message"}
      </button>
    </div>
  );
}
//command-npm create-react-app my-app, cd my-app,(go to files save the file.js with current code) npm start 

//crud.js
const { MongoClient, ObjectId } = require("mongodb");
// Replace with your MongoDB Atlas connection string
const uri = "mongodb+srv://rabiya:12345@cluster9.1gbjnul.mongodb.net/?appName=Cluster9";
const client = new MongoClient(uri);
async function main() {
 try {
 await client.connect();
 console.log("Connected to MongoDB Atlas");
 const db = client.db("companyDB");
 const employees = db.collection("employees");
 // CREATE
 const insertResult = await employees.insertOne({
 name: "Alice Johnson",
 age: 30,
 department: "IT",
 salary: 85000
 });
 console.log(" Inserted:", insertResult.insertedId);
 // READ
 const allEmployees = await employees.find().toArray();
 console.log("All Employees:", allEmployees);
 // UPDATE
 const updateResult = await employees.updateOne(
 { name: "Alice Johnson" },
 { $set: { salary: 90000 } }
 );
 console.log(" Updated Count:", updateResult.modifiedCount);
 // DELETE
 const deleteResult = await employees.deleteOne({ name: "Alice Johnson" });
 console.log(" Deleted Count:", deleteResult.deletedCount);
 } catch (error) {
 console.error(" Error:", error);
 } finally {
 await client.close();
 console.log(" Connection closed");
 }
}
main(); 
//commands-npm -v,npm install mongodb, node crud.js
