template <typename Type> struct mgar {
	Mutex mutex;
	gar<Type> items;
	gar<Type> items_temp;

	void create(this auto& self);
	void destroy(this auto& self);
	bool push(this auto& self, Type item);
	bool pop(this auto& self, Type* out_item);
	ctk::ar<const Type> pop_all(this auto& self);
};