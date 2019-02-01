#ifndef SHARED
#define SHARED
#include <utility>
#include <type_traits>

template <bool not_array = true>
struct DeleteNotAnArray {
	template <typename T>
	void operator()(T * object) {
		delete object;
	}
};
template <>
struct DeleteNotAnArray<false> {
	template <typename T>
	void operator()(T * object) {
		delete[] object;
	}
};




//template <class T>
//struct TDeleter {
//	void operator()( T * object) {
//		//if constexpr(std::is_array<T>::value) {
//		if constexpr(std::is_array<T>::value) {
//			delete[] object;
//		}
//		else {
//			delete object;
//		}
//	}
//};

template<class Type, typename TDeleter = DeleteNotAnArray<true> >
class SharedPTR {
	typedef SharedPTR<Type> t_SharedPTR;
public:
	explicit SharedPTR(Type *pointer = 0)
	{	
		counter = nullptr;
		pObj = nullptr;
		counter = new size_t(1);
		if (pointer != nullptr) {
			pObj = pointer;
		}
	}

	SharedPTR(t_SharedPTR &&sharedPTR) 
	{
		pObj = sharedPTR.pObj;
		counter = sharedPTR.counter;
		sharedPTR.pObj = nullptr;
		sharedPTR.counter = nullptr;
	}

	SharedPTR(const t_SharedPTR& value)
	{
		if (value.counter != 0) {
			(*value.counter)++;
			counter = value.counter;
			pObj = value.pObj;
		}
	}

	~SharedPTR() {
		release();
	}
public:
	t_SharedPTR& operator=(t_SharedPTR &&sharedPTR) {
		if (this != &sharedPTR) {
			release();
			pObj = sharedPTR.pObj;
			counter = sharedPTR.counter;
			sharedPTR.pObj = nullptr;
			sharedPTR.counter = nullptr;
		}
		return *this;
	}

	t_SharedPTR& operator=(Type *pObject) {
		release();
		counter = new size_t(1);
		pObj = pObject;
		return *this;
	}

	t_SharedPTR& operator=(const t_SharedPTR & other) {
		if (this != &other) {
			release();
			(*other.counter)++;
			counter = other.counter;
			pObj = other.pObj;
			
		}
		return *this;
	}
public:
	Type& operator*() const {
		return *pObj;
	} 
	Type* operator->() const {
		return pObj;
	} 
	Type* get() const {
		return pObj;
	} 
	TDeleter& get_deleter() {
		return deleter;
	}
	operator bool() const {
		return (pObj != nullptr);
	} 
public:
	void release() {
		if (counter != nullptr) {
			(*counter)--;
			if (*counter == 0) {
				delete counter;
				if (pObj != nullptr) {
					deleter(pObj);
				}
			}
			counter = nullptr;
			pObj = nullptr;

		}
	} 
	
	void reset(Type *pObject = nullptr) {
		t_SharedPTR(pObject).swap(*this);
		
	} 

	void swap(t_SharedPTR & other) {
		std::swap(pObj, other.pObj);
		std::swap(counter, other.counter);
	}

private:
	Type * pObj;
	size_t * counter;
	TDeleter deleter;
};

#endif

