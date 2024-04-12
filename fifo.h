#ifndef FIFO_H
#define FIFO_H

#include"systemc.h"

template <class T>
class write_if_T : virtual public sc_interface
{
public:
	virtual void write(T) = 0;
	virtual void reset() = 0;
};

template <class T>
class read_if_T : virtual public sc_interface
{
public:
	virtual void read(T &) = 0;
	virtual int num_available() = 0;
};

template <class T>
class fifo_T : public sc_channel,
	public write_if_T<T>,
	public read_if_T<T>
{
public:

SC_HAS_PROCESS(fifo_T);

fifo_T( sc_module_name name_, int max_=5000) :  sc_module(name_)
{
	max = max_;
	data = new T[max];
	num_elements = first = 0;
}

~fifo_T(){ delete data;}

void write(T c) {
if (num_elements == max)
	wait(read_event);
	data[(first + num_elements) % max ] = c;
	++ num_elements;
	write_event.notify();
}
void read(T& c) {
	if (num_elements == 0)
	wait(write_event);
	c = data[first];
	-- num_elements;
	first = (first + 1) % max;
	read_event.notify();
} 
void reset() { num_elements = first = 0; }
int num_available() {return num_elements;}



	int max; 
	T *data;
	int num_elements, first;
private:
	sc_event write_event, read_event;
};


#endif