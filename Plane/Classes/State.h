#ifndef  __STATE_H__
#define  __STATE_H__


template <class  own>
class state
{
public:
	state(void) {}
	~state(void)  {}

	virtual void   enter(own *)=0;
	virtual void   execute(own*)=0;
	virtual void   exit(own *)=0;
	virtual void   handleEvent(own *)=0;

};

#endif