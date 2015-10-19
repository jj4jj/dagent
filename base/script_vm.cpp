#include "script_vm.h"
#include "logger.h"
extern "C" {
#include "python2.7/Python.h"
}


struct python_vm_t {
	bool	myown;
};

struct script_vm_t{
	script_vm_type	type;
	std::string		path;
	python_vm_t	 *	python;
	script_vm_t(){
		python = nullptr;
		type = script_vm_type::SCRIPT_VM_NONE;
	}
};

static python_vm_t * _create_vm_python(const script_python_conf_t & conf){

	python_vm_t * vm = new python_vm_t();
	vm->myown = true;
	if (Py_IsInitialized()){
		LOGP("python vm has been inited by other module.");
		vm->myown = false;
	}
	else {
		Py_InitializeEx(0);
	}
	return vm;
}
static void _destroy_vm_python(python_vm_t * vm){
	if (vm){
		if (vm->myown){
			Py_Finalize();
		}
		delete vm;
	}
}
static int _run_python_file(python_vm_t * vm, const char* file){
	FILE * fp = fopen(file, "r");
	if (!fp){
		LOGP("open file error :%d for:%s", errno, strerror(errno));
		return -1;
	}
	return PyRun_SimpleFileExFlags(fp, file, 1, NULL);
}

static int _run_python_string(python_vm_t * vm, const char * str){
	return PyRun_SimpleString(str);
}

////////////////////////////////////
script_vm_t*	script_vm_create(const script_vm_config_t & conf){
	auto vm = new script_vm_t();
	switch (conf.type){
	case SCRIPT_VM_PYTHON:
		vm->python = _create_vm_python(conf.u.python);
		if (!vm->python){
			delete vm;
			return nullptr;
		}
		break;
	default:
		return nullptr;
	}
	vm->type = conf.type;
	if (conf.path){
		vm->path = conf.path;
	}
	return vm;
}
void			script_vm_destroy(script_vm_t * vm){
	if (vm){
		switch (vm->type){
		case SCRIPT_VM_PYTHON:
			_destroy_vm_python(vm->python);
			vm->python = nullptr;
			break;
		default:break;
		}
		delete vm;
	}
}
int				script_vm_run_file(script_vm_t * vm, const char * file){
	std::string filepath = file;
	if (file[0] != '/' && !vm->path.empty()){
		filepath = vm->path + "/" + file;
	}
	switch (vm->type){
	case SCRIPT_VM_PYTHON:
		return _run_python_file(vm->python, filepath.c_str());
	default:
		LOGP("not support type:%d", vm->type);
		return -1;
	}
}
int				script_vm_run_string(script_vm_t * vm, const char * str){
	switch (vm->type){
	case SCRIPT_VM_PYTHON:
		return _run_python_string(vm->python, str);
	default:
		LOGP("not support type:%d", vm->type);
		return -1;
	}
}


//for python
void					script_vm_export(script_vm_t * vm, const script_vm_python_export_t & export_){
	return;
}