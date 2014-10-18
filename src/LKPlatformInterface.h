#ifndef KCLIB_LKNETWORKINTERFACE_H
#define KCLIB_LKNETWORKINTERFACE_H

#include <map>
#include <iostream>

template<typename T>
class LKPlatformInterface
{
public:
	virtual ~LKPlatformInterface() {};
	
	// --> Per-type Registry singleton
	class Registry
	{
	public:
		template<typename T2>
		struct register_t
		{
			register_t(int priority)
			{
				std::cout << "Registering a module with Prio " << priority << std::endl;
				LKPlatformInterface<T>::Registry::get().all.insert(std::make_pair(priority, &register_t<T2>::create));
			};
			
			// Just create a new T2; used for entry::createfn
			static T* create() { return new T2; }
		};
		
		static Registry& get()
		{
			// This is threadsafe... IF THE PROGRAM IS COMPILED WITH C++11.
			// (There's no safe, portable way in non-boost 03; mutex is 11 too)
			static Registry _instance;
			return _instance;
		};
		
		// All implementations of T, keyed by priority - maps are sorted, which
		// means that the last element (rbegin()) will be the one with the
		// highest priority - that's the one we want to use!
		std::map<int,T*(*)()> all;
		
	private:
		// It's a singleton, don't go creating local instances of it!
		Registry() {};
		Registry(const Registry&) = delete;
	};
	
	
	
	// Factory function for creating an instance of the preferred impl
	static T* create()
	{
		// Call the createfn of the impl with the highest priority
		auto& impls = LKPlatformInterface<T>::Registry::get().all;
		return impls.rbegin()->second();
	};

protected:
	// Impls should only be createable with create()
	LKPlatformInterface() {};
	// They should not be copyable
	LKPlatformInterface(const LKPlatformInterface&) = delete;
};

#define _REGISTER_IMPL_VNAME(T) _module_##T##_reg
#define REGISTER_IMPL(baseT, T, priority) static baseT::Registry::register_t<T> _REGISTER_IMPL_VNAME(T)(priority);

#endif
