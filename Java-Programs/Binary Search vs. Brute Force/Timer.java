
public class Timer {
	long _starttime = 0;
	long _endtime = 0;
	long elapsed = 0;
	
	public void start(){
		this._starttime = System.nanoTime();
	}
	public void end(){
		this._endtime = System.nanoTime();
	}
	public long totalttime(){
		return this._endtime - this._starttime;
	}
	
	public long get_starttime() {
		return _starttime;
	}
	public void set_starttime(long _starttime) {
		this._starttime = _starttime;
	}
	public long get_endtime() {
		return _endtime;
	}
	public void set_endtime(long _endtime) {
		this._endtime = _endtime;
	}
	
}
