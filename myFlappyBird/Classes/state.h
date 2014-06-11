#ifndef  __STATE_H__
#define  __STATE_H__


template <class  own>
class state
{
public:
	state(void) {}
	~state(void)  {}

	virtual void   enter(own *){}
	virtual void   execute(own*){}
	virtual void   exit(own *){}
	virtual void   handleEvent(own *){}
};

#endif