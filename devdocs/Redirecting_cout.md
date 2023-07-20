# Redirecting std::cout

It is often useful during testing to redirect std::cout to a string so output can be compared to expected values.

The following code snippet illustrates how to redirect std::cout.

~~~
auto* old_buffer = std::cout.rdbuf(); // capture std::cout's buffer (note: it would be better to use RAII here)
std::ostringstream os;
std::cout.rdbuf(os.rdbuf()); // assign the string stream's buffer to std::cout so std::cout writes to the string buffer

std::cout << "Testing 1,2,3" <<std::endl;

std::cout.rdbuf(old_buffer); // restore std::cout's buffer

Assert::AreEqual("Testing 1,2,3",os.str().c_str()); // test against the expected value
~~~
