<img src="https://www.colorado.edu/cs/profiles/express/themes/ucb/images/cu-boulder-logo-text-black.svg" alt="CU Boulder Logo" width="500">

# CSCI 2270: Data Structures <br/> University Courses Database Project

## Introduction
The objective of this project is to write an application that reads a list of University courses from a data file and then inserts them into two separate hash tables. The first hash table will use the Open Addressing collision resolution scheme and the second hash table will use the Chaining collision resolution scheme. Users should be able to search the hash tables for a specific course number or display all of the courses. It’s your objective to compare and contrast the hashing collision resolution methods. Additionally, the application should maintain a list of courses taught by each professor by using a binary search tree data structure. Users should be able to search for a professor and view all of the courses taught by the Professor.

## Getting Started
1. Download the project pdf writeup located within this starter repo.<br/>
2. Download the PowerPoint slide deck [Getting Started With GitHub Classroom Workflow](https://docs.google.com/presentation/d/1B0yZb6twQ_NVL8PripCL7AkeIKSrR8_M/edit?usp=sharing&ouid=115561230768383364768&rtpof=true&sd=true).<br/>
3. Download the [GitHub presentation slide deck](https://drive.google.com/file/d/12mMxMGRrpnkSuz08FUlvkhC-9WJ4JHns/view?usp=sharing) created by Asa Ashraf.<br/>
4. View the GitHub lecture videos [Part I](https://drive.google.com/file/d/1P4iqEbt9Nx68-Nq0FxxpdBZCrbkx5cN3/view?usp=sharing) and [Part II](https://drive.google.com/file/d/1EFYq_qJsV3QNcx_W86nz2KFpQUhSn9jF/view?usp=sharing) given by Asa Ashraf.

## Disclaimer
Students are not allowed to share this code or make it public at any time, even after the course has completed.

## Deliverables
1. Does one hashing collision resolution work better than the other? Consider the datasets we used and a much larger dataset with 1 million records. Explain your answer.<br/><br/>
    When looking at the results when all functions are ran, it can be seen the open adressing has slightly more collisions as well as more searches to find an open bucket in comparsion to chaing collision resoultion. However, while it takes longer to insert each element, there are less searches needed when accessing the data, as in open adressing, the search funciton does not need to traverse an entire linked list.<br/>
    This is espeically true when considering much larger datasets; the quadratic probing open addressing collision resolution scheme will work better than the chaining collision resolution scheme as it spreads the data across the table instead of using a linked list to add data to the intial bucekt that is given by the hash function. As the data set gets larger and larger the chances of collisions increases, thus a linked list would have more elements chained together whcih would increase the runtime when searching for coruses. Thus, the complexity for a search would be O(n). However, on the other hand, to search a hash table that utizlies open adressing would have less elements that would have to be traversed before posiblly finding a match. <br/><br/>


2. We used the same BST for both hashing mechanisms. What alternative data structure would you advise? Why?<br/><br/>
    Instead of using a BST I would advise using another hash table as we never needed to access the courses in alphabetical order. Thus, we could potentially reduce the search complexity of searching and even inserting to an average performance of O(1) and a worst-case runtime of O(n) with collisions. This would incerease the performance from O(log(n)) that is currently used for the BST. Overall, this would allow for more efficent and faster runtime when storing and searching for the professors in the data structure.<br/>

3. Explain a few ways you could improve the application.<br/><br/>
    One way the application could be imporved would be to first create an extra header and cpp file that contained code that is used in both the HashOpenAddressing.cpp and HashChaining.cpp files. This would reduce redundancy and would make it easier to build upon the code if new functions needed to implemented. This would also make testing easier and would lead to cleaner code.<br/>
    Another way that this applicaiton could be impoved would be to balance the tree if a BST is still used. By performing rotations and performing colorings, a RBT could be created that would guarantee the wrost case runtime to be O(log n). <br/>
    Furthermore, the application could be updated to include more menu options that would allow for finer control over searching or even insertion. This could first be completed by added a range of years to the search function that would allow the user to search for what courses were taught what years or even what classes a certain professor taught in a specific year or range of years. This could also be updated so that the insertion option could be run mulitple times to allow for updated lists to be be added while the program is still running.<br/>
