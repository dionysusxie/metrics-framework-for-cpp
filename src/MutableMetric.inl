//////////////////////////////////////////////////////////////////////////////////////////
//
// class MutableCounter<T>:
//

template <class T>
MutableCounter<T>::MutableCounter(const BasicItemReadOnly& info, T init_value):
        MutableMetric(info),
        value_(init_value) {
}

template <class T>
T MutableCounter<T>::value() {
    boost::shared_lock<boost::shared_mutex> read_lock(this->value_mutex_);
    return value_;
}

template <class T>
void MutableCounter<T>::incr(T delta) {
    boost::lock_guard<boost::shared_mutex> write_lock(this->value_mutex_);
    value_ += delta;
    this->setChanged();
}

template <class T>
void MutableCounter<T>::snapshotImpl(MetricsRecordBuilder& builder) {
    builder.addCounter(this->getReadOnlyItem(), value());
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class MutableGauge<T>:
//

template <class T>
MutableGauge<T>::MutableGauge(const BasicItemReadOnly& info, T init_value):
        MutableMetric(info),
        value_(init_value) {
}

template <class T>
T MutableGauge<T>::value() {
    boost::shared_lock<boost::shared_mutex> read_lock(this->value_mutex_);
    return value_;
}

template <class T>
void MutableGauge<T>::incr(T delta) {
    boost::lock_guard<boost::shared_mutex> write_lock(this->value_mutex_);
    value_ += delta;
    this->setChanged();
}

template <class T>
void MutableGauge<T>::decr(T delta) {
    boost::lock_guard<boost::shared_mutex> write_lock(this->value_mutex_);
    value_ -= delta;
    this->setChanged();
}

template <class T>
void MutableGauge<T>::set(T new_value) {
    boost::lock_guard<boost::shared_mutex> write_lock(this->value_mutex_);
    value_ = new_value;
    this->setChanged();
}

template <class T>
void MutableGauge<T>::snapshotImpl(MetricsRecordBuilder& builder) {
    builder.addGauge(this->getReadOnlyItem(), value());
}
