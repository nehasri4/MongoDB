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
