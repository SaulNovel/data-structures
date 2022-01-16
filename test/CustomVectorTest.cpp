#include <gtest/gtest.h>

#include <Array/CustomVector.h>

#include <string>
#include <vector>
#include <deque>

using std::string;

/* --- Scalar types --- */
template <typename T>
class VectorScalarTypesTest : public testing::Test {
 public:
  using VectorScalarTypes = Vector<T>;
};

template <>
class VectorScalarTypesTest<std::string> : public testing::Test {
 public:
  using VectorScalarTypes = Vector<std::string>;
};

struct Point
{
    double x;
    double y;

    bool operator==(const Point& other) const
    {
        return (x == other.x) && (y == other.y);
    }
};

std::ostream& operator<<(std::ostream& os, const Point& point)
{
    return os << "x: " << point.x << ", y: " << point.y;
}

/* Helper function to return a value depending on the parametrized type tested
    - The current implementation requires dedicated templates for non POD types TODO: cast non POD to char*?
*/
template <typename T>
const T getValue()
{
    int val = rand() / RAND_MAX;
    return static_cast<T>(val);
}

template <>
const std::string getValue()
{
    const int32_t MAX = 26;
    const int32_t strSize = 26;
    char alphabet[MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n', 
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };
    std::string randomStr = "";
    for (int32_t i = 0; i < strSize; i++) {
        randomStr = randomStr + alphabet[rand() % strSize];
    }      
    return randomStr;
}

template <>
const Point getValue()
{
    return {getValue<double>(), getValue<double>()};
}

template <typename T>
const T getInitValue()
{
    return T();
}

using VectorScalarTypes = ::testing::Types<char, int32_t, double, Point, std::string>;

TYPED_TEST_SUITE(VectorScalarTypesTest, VectorScalarTypes);

/* --- Container types --- */

template <typename T>
class VectorNonScalarTypesTest : public testing::Test {
 public:
  using VectorNonScalarTypes = Vector<T>;
};

template <typename T>
const T getNonScalarValue(size_t size)
{
    typename T::value_type value = static_cast<typename T::value_type>(rand()) / static_cast<typename T::value_type>(RAND_MAX);
    return T(size, value);
}

// Dynamic Sequence Containers
using VectorNonScalarTypes = ::testing::Types<std::vector<float>, std::deque<float>>;

TYPED_TEST_SUITE(VectorNonScalarTypesTest, VectorNonScalarTypes);


TYPED_TEST(VectorScalarTypesTest, Empty_constructor) 
{
    {
        typename TestFixture::VectorScalarTypes temp;
        EXPECT_EQ(0, temp.size());
    }
    {
        typename TestFixture::VectorScalarTypes temp({});
        EXPECT_EQ(0, temp.size());
    }

    {
        size_t size = 20;
        typename TestFixture::VectorScalarTypes temp(size);
        EXPECT_EQ(size, temp.size());

        for (size_t i = 0; i < temp.size(); ++i)
        {
            ASSERT_EQ(getInitValue<TypeParam>(), temp[i]) << " failed on index: " << i;
        }
    }
}

TYPED_TEST(VectorScalarTypesTest, Constructor_values)
{
    // TODO: update when iterators will be implmented
    // ASSERT_THAT(std::vector<uint8_t>(buffer, buffer + buffer_size), ::testing::ElementsAreArray(expect));

    size_t size = 20;
    TypeParam value = getValue<TypeParam>();

    typename TestFixture::VectorScalarTypes temp(size, value);
    for (size_t i = 0; i < temp.size(); ++i)
    {
        ASSERT_EQ(value, temp[i]) << " failed on index: " << i;
    }
}

TYPED_TEST(VectorScalarTypesTest, Move_constructor)
{
    size_t size = 20;
    TypeParam value = getValue<TypeParam>();

    typename TestFixture::VectorScalarTypes temp(size, value);
    typename TestFixture::VectorScalarTypes temp2(std::move(temp));
    
    EXPECT_EQ(0, temp.size());
    EXPECT_EQ(0, temp.capacity());
    EXPECT_EQ(size, temp2.size());

    for (size_t i = 0; i < temp2.size(); ++i)
    {
        ASSERT_EQ(value, temp2[i]) << " failed on index: " << i;
    }
}

TYPED_TEST(VectorScalarTypesTest, Copy_constructor)
{
    size_t size = 20;
    TypeParam value = getValue<TypeParam>();

    typename TestFixture::VectorScalarTypes temp(size, value);
    typename TestFixture::VectorScalarTypes temp2(temp);
    
    EXPECT_EQ(temp.size(), temp2.size());
    EXPECT_EQ(temp.capacity(), temp2.capacity());

    for (size_t i = 0; i < temp2.size(); ++i)
    {
        ASSERT_EQ(temp[i], temp2[i]) << " failed on index: " << i;
    }
}

TYPED_TEST(VectorScalarTypesTest, Move_assignment)
{
    size_t size = 20;
    TypeParam value = getValue<TypeParam>();

    typename TestFixture::VectorScalarTypes temp(size, value);
    typename TestFixture::VectorScalarTypes temp2;

    temp2 = std::move(temp);

    EXPECT_EQ(0, temp.size());
    EXPECT_EQ(0, temp.capacity());
    EXPECT_EQ(size, temp2.size());
    for (size_t i = 0; i < temp2.size(); ++i)
    {
        ASSERT_EQ(value, temp2[i]) << " failed on index: " << i;
    }

    typename TestFixture::VectorScalarTypes temp3 = std::move(temp2);

    EXPECT_EQ(0, temp2.size());
    EXPECT_EQ(0, temp2.capacity());
    EXPECT_EQ(size, temp3.size());
    for (size_t i = 0; i < temp3.size(); ++i)
    {
        ASSERT_EQ(value, temp3[i]) << " failed on index: " << i;
    }
}

TYPED_TEST(VectorScalarTypesTest, Copy_assignment)
{
    size_t size = 20;
    TypeParam value = getValue<TypeParam>();

    typename TestFixture::VectorScalarTypes temp(size, value);
    typename TestFixture::VectorScalarTypes temp2;

    temp2 = temp;

    EXPECT_EQ(temp.capacity(), temp2.capacity());
    EXPECT_EQ(temp.size(), temp2.size());
    for (size_t i = 0; i < temp2.size(); ++i)
    {
        ASSERT_EQ(temp[i], temp2[i]) << " failed on index: " << i;
    }

    typename TestFixture::VectorScalarTypes temp3 = temp2;
    
    EXPECT_EQ(temp2.capacity(), temp3.capacity());
    EXPECT_EQ(temp2.size(), temp3.size());
    for (size_t i = 0; i < temp3.size(); ++i)
    {
        ASSERT_EQ(temp2[i], temp3[i]) << " failed on index: " << i;
    }
}

TYPED_TEST(VectorScalarTypesTest, Reserve)
{
    size_t size = 20;
    size_t capacity = 200;
    
    typename TestFixture::VectorScalarTypes temp(size);

    temp.reserve(capacity);

    EXPECT_EQ(size, temp.size());
    EXPECT_EQ(capacity, temp.capacity());

    // capacity < current capacity does nothing
    temp.reserve(capacity-1);
    EXPECT_EQ(capacity, temp.capacity());
}

TYPED_TEST(VectorScalarTypesTest, Resize)
{
    size_t size = 20;
    size_t newSize = 200;
    TypeParam value = getValue<TypeParam>();
    TypeParam initValue = getInitValue<TypeParam>();
    typename TestFixture::VectorScalarTypes temp(size, value);

    {
        temp.resize(newSize);    

        ASSERT_EQ(newSize, temp.size());
        for (size_t i = size; i < temp.size(); ++i) {
            ASSERT_EQ(initValue, temp[i]) << " failed on index: " << i;
        }
    }

    {
        TypeParam value2 = getValue<TypeParam>();
        newSize = 300;
        size_t prevSize = temp.size();
        temp.resize(newSize, value2);

        ASSERT_EQ(newSize, temp.size());
        for (size_t i = prevSize; i < temp.size(); ++i) {
            ASSERT_EQ(value2, temp[i]) << " failed on index: " << i;
        }

    }

    {
        TypeParam value2 = getValue<TypeParam>();    
        newSize = 100;
        temp.resize(newSize, value2);

        ASSERT_EQ(newSize, temp.size());
        for (size_t i = 0; i < temp.size(); ++i) {
            if (i < size) {
                ASSERT_EQ(value, temp[i]) << " failed on index: " << i;
                continue;
            }
            ASSERT_EQ(initValue, temp[i]) << " failed on index: " << i;        
        }
    }

    {
        TypeParam value2 = getValue<TypeParam>();    
        newSize = 0;
        temp.resize(newSize, value2);

        ASSERT_EQ(newSize, temp.size());
    }
}

TYPED_TEST(VectorScalarTypesTest, Element_access)
{
    size_t size = 20;
    TypeParam value = getValue<TypeParam>();
    typename TestFixture::VectorScalarTypes temp(size, value);
    for (size_t i = 0; i < temp.size(); ++i) {
        ASSERT_EQ(value, temp.at(i)) << " failed on index: " << i;
    }
    
    TypeParam newValue = getValue<TypeParam>();
    temp.at(0) = newValue; 
    ASSERT_EQ(newValue, temp.at(0));

    const typename TestFixture::VectorScalarTypes tempConst(size, value);
    for (size_t i = 0; i < temp.size(); ++i) {
        ASSERT_EQ(value, tempConst.at(i)) << " failed on index: " << i;
    }

    try {
        TypeParam val = temp.at(size);
        static_cast<void>(val);
        throw;
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(), std::string("index " + std::to_string(size) + " is out of range"));
    }
    catch(...) {
        FAIL() << "Expected std::out_of_range";
    }

    try {
        TypeParam val = tempConst.at(size);
        static_cast<void>(val);
        throw;
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(), std::string("index " + std::to_string(size) + " is out of range"));
    }
    catch(...) {
        FAIL() << "Expected std::out_of_range";
    }
}

TYPED_TEST(VectorScalarTypesTest, Data)
{
    size_t size = 20;
    TypeParam value = getValue<TypeParam>();
    typename TestFixture::VectorScalarTypes temp(size, value);
    TypeParam* data = temp.data();
    for (size_t i = 0; i < temp.size(); ++i) {
        ASSERT_EQ(value, data[i]) << " failed on index: " << i;
    }
    
}

TYPED_TEST(VectorScalarTypesTest, Push_back)
{

    size_t size = 20;
    typename TestFixture::VectorScalarTypes temp(size);
    TypeParam value = getValue<TypeParam>();

    temp.push_back(value);
    ASSERT_EQ(size+1, temp.size());
    ASSERT_EQ(size*2, temp.capacity());
    ASSERT_EQ(value, temp[size]);

    TypeParam value2 = value;
    temp.push_back(std::move(value));
    ASSERT_EQ(size+2, temp.size());
    ASSERT_EQ(value2, temp[size+1]);
    if (!std::is_trivially_default_constructible<TypeParam>::value)
    {
        // TODO: it expects that the object is left on a valid state after std::move
        ASSERT_EQ(getInitValue<TypeParam>(), value);
    }
}

TYPED_TEST(VectorScalarTypesTest, Emplace_back)
{

    size_t size = 20;
    typename TestFixture::VectorScalarTypes temp(size);
    TypeParam value = getValue<TypeParam>();

    TypeParam value2 = value;
    temp.emplace_back(std::move(value));
    ASSERT_EQ(size+1, temp.size());
    ASSERT_EQ(size*2, temp.capacity());

    ASSERT_EQ(value2, temp[size]);
}


TYPED_TEST(VectorScalarTypesTest, Pop_back)
{
    typename TestFixture::VectorScalarTypes temp;

    TypeParam initValue = getInitValue<TypeParam>();
    temp.push_back(initValue);
    TypeParam value = getValue<TypeParam>();
    temp.push_back(value);
    temp.push_back(getValue<TypeParam>());

    size_t size = temp.size();
    size_t capacity = temp.capacity();

    temp.pop_back();

    ASSERT_EQ(--size, temp.size());
    ASSERT_EQ(capacity, temp.capacity());
    ASSERT_EQ(temp.at(size-1), value);

    temp.pop_back();

    ASSERT_EQ(--size, temp.size());
    ASSERT_EQ(temp.at(size-1), initValue);
    ASSERT_EQ(capacity, temp.capacity());

    temp.pop_back();

    ASSERT_EQ(0, temp.size());
    ASSERT_EQ(capacity, temp.capacity());
}

TYPED_TEST(VectorScalarTypesTest, Clear)
{
    size_t size = 20;    
    typename TestFixture::VectorScalarTypes temp(size);
    size_t capacity = temp.capacity();

    temp.clear();

    EXPECT_EQ(capacity, temp.capacity());
    EXPECT_EQ(0, temp.size());
}

TYPED_TEST(VectorScalarTypesTest, Range_Loop)
{
    size_t size = 20;
    TypeParam initValue = getValue<TypeParam>();
    typename TestFixture::VectorScalarTypes temp(size, initValue);

    // Ranged loop
    for (TypeParam& value : temp)
    {
        ASSERT_EQ(value, initValue);
    }

    // Foreach loop
    std::for_each(temp.begin(), temp.end(), [initValue](TypeParam value) {
         ASSERT_EQ(value, initValue);
    });

    std::for_each(temp.cbegin(), temp.cend(), [initValue](const TypeParam& value) {
        ASSERT_EQ(value, initValue);
    });
}

TYPED_TEST(VectorScalarTypesTest, Iterators)
{
    size_t size = 20;
    TypeParam initValue = getValue<TypeParam>();
    typename TestFixture::VectorScalarTypes temp(size, initValue);

    // Loop with Normal iterator
    using Iterator = typename TestFixture::VectorScalarTypes::iterator;
    for (Iterator it = temp.begin(); it != temp.end(); ++it)
    {
        ASSERT_EQ(*it, initValue);
        TypeParam newValue = getValue<TypeParam>();
        *it = newValue;
        ASSERT_EQ(*it, newValue);
    }

    // Loop with constant iterator
    typename TestFixture::VectorScalarTypes temp2(size, initValue);
    using const_Iterator = typename TestFixture::VectorScalarTypes::const_iterator;
    for (const_Iterator it = temp2.cbegin(); it != temp2.cend(); ++it)
    {
        ASSERT_EQ(*it, initValue);
    }
}

// TODO make it parametrized
TYPED_TEST(VectorNonScalarTypesTest, Containers)
{
    size_t containerSize = 20;
    TypeParam container = getNonScalarValue<TypeParam>(containerSize);
    typename TypeParam::value_type initValue = container[0];
        
    size_t size = 20;
    typename TestFixture::VectorNonScalarTypes temp(size, container);

    for (const TypeParam& containerRef : temp)
    {
        for (const float value : containerRef)
        {
            ASSERT_EQ(value, initValue);
        }
    }
}

struct A
{
    double x;
    A() 
    {
        throw std::runtime_error("constructor throws");
    }
};

TEST(VectorTest, Constructor_throws)
{
    // Implement default constructor noexcept
    Vector<A> temp;
    //std::vector<A> temp(20);
}

int main(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
} 
