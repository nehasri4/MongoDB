// db.js 

const { MongoClient } = require("mongodb"); 

const uri = "mongodb+srv://<username>:<password>@<cluster>.mongodb.net/"; 

const client = new MongoClient(uri); 

async function run() { 

 try { 

 await client.connect(); 

 console.log("Connected to MongoDB Atlas"); 

 const db = client.db("schoolDB"); // This creates a reference to a database 

 const students = db.collection("students"); // Creates reference to collection 

 await db.createCollection("teachers"); 

 console.log("'teachers' collection created in 'schoolDB'"); 

 await students.insertOne({ name: "Alice", grade: "A" }); 

 console.log( Inserted a document into 'students' collection"); 

 await db.collection("teachers").drop(); 

 console.log(" 'teachers' collection dropped"); 

 await db.dropDatabase(); 

 console.log(" 'schoolDB' database dropped");
} catch (error) { 

 console.error("Error:", error); 

 } finally { 

 await client.close(); 

 console.log(" Connection closed"); 

 } 

} 

run();








// app.js

// 1. ExpressJS - Data, URL Building
// A program to define a route, handle a request, handle parameters, query parameters, and URL building.

const express = require('express');
const app = express();
const port = 3000;

// Middleware to parse JSON bodies
app.use(express.json());

/**
 * 1 Basic route
 */
app.get('/', (req, res) => {
    res.send('Welcome to the Express.js example!');
});

/**
 * 2 Route parameters
 */
app.get('/users/:id', (req, res) => {
    const userId = req.params.id;
    res.send(`User ID received: ${userId}`);
});

/**
 * 3 Query parameters
 * Example: GET /search?q=nodejs&page=2
 */
app.get('/search', (req, res) => {
    const query = req.query.q;
    const page = req.query.page || 1;
    res.send(`Search query: ${query}, Page: ${page}`);
});

/**
 * 4 POST request with JSON body
 * Example: POST /users with { "name": "Alice" }
 */
app.post('/users', (req, res) => {
    const name = req.body.name || "sample";
    res.status(201).send(`User '${name}' created successfully!`);
});

/**
 * 5 URL building example
 * Using `req.baseUrl` and `req.path`
 */
app.get('/info', (req, res) => {
    const fullUrl = `${req.protocol}://${req.get('host')}${req.originalUrl}`;
    res.send(`Full URL of this request: ${fullUrl}`);
});

// Start server
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});










import React from "react";
import { BrowserRouter as Router, Routes, Route, Link } from "react-router-dom";
import Home from "./Home";
import About from "./About";
import Contact from "./Contact";

function App() {
  return (
    <Router>
      <div style={{ fontFamily: "system-ui", padding: 20 }}>
        <h2>React Router Example</h2>

        {/* Navigation Links */}
        <nav style={{ marginBottom: 20 }}>
          <Link to="/" style={{ marginRight: 10 }}>Home</Link>
          <Link to="/about" style={{ marginRight: 10 }}>About</Link>
          <Link to="/contact">Contact</Link>
        </nav>

        {/* Define Routes */}
        <Routes>
          <Route path="/" element={<Home />} />
          <Route path="/about" element={<About />} />
          <Route path="/contact" element={<Contact />} />
        </Routes>
      </div>
    </Router>
  );
}

export default App;
import React from "react";

function Home() {
  return <h3>Welcome to the Home Page</h3>;
}

export default Home;
import React from "react";

function About() {
  return <h3>This is the About Page</h3>;
}

export default About;
import React from "react";

function Contact() {
  return <h3>This is the Contact Page</h3>;
}

export default Contact;

