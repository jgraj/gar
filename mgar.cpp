template <typename Type>
void mgar<Type>::create(this auto& self) {
	self.mutex.create();
	self.items.create_auto();
	self.items_temp.create_auto();
}

template <typename Type>
void mgar<Type>::destroy(this auto& self) {
	self.mutex.destroy();
	self.items.destroy();
	self.items_temp.destroy();
}

template <typename Type>
bool mgar<Type>::push(this auto& self, Type item) {
	self.mutex.lock();
	bool was_empty = self.items.len == 0;
	self.items.push(item);
	self.mutex.unlock();
	return was_empty;
}

template <typename Type>
bool mgar<Type>::pop(this auto& self, Type* out_item) {
	self.mutex.lock();
	bool found = false;
	if (self.items.len > 0) {
		*out_item = self.items.remove(0);
		found = true;
	}
	self.mutex.unlock();
	return found;
}

template <typename Type>
ctk::ar<const Type> mgar<Type>::pop_all(this auto& self) {
	self.mutex.lock();
	self.items_temp.clear();
	ctk::swap<ctk::gar<Type>>(&self.items, &self.items_temp);
	self.mutex.unlock();
	return self.items_temp.to_ar();
}