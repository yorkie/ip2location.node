
IP2Location.node
=======================

[ip2location.com](http://www.ip2location.com/) bindings for nodejs

### Usage

see [example](example.js)

### API

* `IP2Location(path, mtype)` your ip2location binrary file path

  * `path` your binary path

  * `mtype` the way you access binary data later, you should set it:

    * `use_cache` default value

    * `use_shared_memory`

    * `use_file_io`

* `.query(ip)`: list all profile

### Benchmark

100000 calls to `query` means 180+ ms

### Installation

```
$ npm install ip2location.node --save
```

### License

MIT