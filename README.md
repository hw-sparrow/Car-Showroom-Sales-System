<h1 align="center">Car Showroom Sales System</h1>
<br>
<h2>Project Overview</h2>
The Car Showroom Sales System is a C++ application designed to manage the operations of a car showroom. It enables users to add various types of cars (new, used, and imported), store their details, perform sales transactions, calculate tax based on car age, and maintain persistent records in text files. The system is built using Object-Oriented Programming principles such as Inheritance, Polymorphism, Encapsulation, Templates, and dynamic memory allocation.
<br><br>
<h2>Objectives</h2>
<ul>
  <li>Efficiently manage a car showroom's inventory and customer sales.</li>
  <li>Support different car types: new, used, and imported.</li>
  <li>Maintain sales history and showroom inventory persistently using file handling.</li>
  <li>Provide modularity and scalability for future enhancements.</li>
</ul>
<br>
<h2>Key Features</h2>
<ol>
  <li><b> Showroom Management: -</b></li>
    <ul>
      <li>Takes basic showroom details (Name, Contact Number, Address, Tax Registration Number).</li>
      <li>Display functionality for stored showroom data.</li>
    </ul>
  <li><b>Car Management: -</b></li>
    <ul>
      <li>Abstract Car class encapsulates common car attributes:</li>
        <ul>
          <li>Model</li>
          <li>Price</li>
          <li>Engine Size</li>
          <li>Transmission Type</li>
          <li>Engine Number</li>
          <li>Chassis Number</li>
          <li>Manufacture Year</li>
        </ul>
      <li>Derived classes:</li>
        <ul>
          <li><b><i>UsedCar</i></b> adds RegistrationNo.</li>
          <li><b><i>ImportedCar</i></b> extends UsedCar by adding AuctionDate and AuctionGrade.</li>
        </ul>
      <li>Cars are dynamically allocated and managed using a pointer-based array.</li>
    </ul>
  <li><b>Tax Calculation: -</b></li>
    Based on the car’s age:
      <ul>
        <li>Cars older than 5 years are taxed at 15% of their price.</li>
        <li>Newer cars are tax-free.</li>
      </ul>
  <li><b>Customer Handling: -</b></li>
    <ul>
      <li>Stores details such as:</li>
        <ul>
          <li>Customer Name</li>
          <li>CNIC</li>
          <li>Employee ID</li>
        </ul>
      <li>Allows input and display of customer data during transactions.</li>
    </ul>
  <li><b>Sales Transactions: -</b></li>
    <ul>
      <li>Associates a customer with a car.</li>
      <li>Computes tax and total price.</li>
      <li>Generates and prints a sale receipt.</li>
      <li>Saves the transaction record to SoldCars.txt.</li>
      <li>Removes the sold car from inventory and updates Showroom.txt.</li>
    </ul>
  <li><b>File Handeling: -</b></li>
    <ul>
      <li>Showroom.txt: Maintains current inventory of cars.</li>
      <li>SoldCars.txt: Logs completed sales transactions.</li>
      <li>Uses ofstream with append (ios::app) and truncate (ios::trunc) modes.</li>
    </ul>
  <li><b>Error Handeling: -</b></li>
    <ul>
      <li>Ensures file streams are successfully opened before writing.</li>
      <li>Validates user input for car selection during sales.</li>
      <li>Uses cin.ignore() appropriately to handle mixed input modes (cin + getline).</li>
    </ul>
</ol>
<br>
<h2>Repository Structure</h2>
Car-Showroom-Sales-System/
<br>
├── Car-Showroom-Sales-System.cpp ---> Main C++ source file
<br>
├── Showroom.txt ---> Maintains current inventory of cars (created during project compilation)
<br>
├── SoldCars.txt ---> Logs completed sales transactions (created during project compilation)
<br>
├── README.md ---> Project documentation
