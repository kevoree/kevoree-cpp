#include <kevoree-tools/DynamicLoader/DynamicLoader.h>
#include <map>

DynamicLoader::DynamicLoader(Bootstraper *bootstrap)
{
	this->bootstrap = bootstrap;	
}

void DynamicLoader::setModelService(KevoreeModelHandlerService *mservice){
	this->mservice = mservice;
}


DeployUnit * DynamicLoader::select_du_architecture(TypeDefinition *type) {
	DeployUnit *du=NULL;

	// TODO need to add in the metamodel
	for ( std::map<string,DeployUnit*>::const_iterator it = (type->deployUnit).begin();  it != (type->deployUnit).end(); ++it) {
		return it->second;
	}
	return du;
}


bool DynamicLoader::register_instance(Instance *i)
{

	try
	{
		TypeDefinition *type = i->typeDefinition;
		DeployUnit *du=NULL;

		if(type == NULL)
		{
			LOGGER_WRITE(Logger::ERROR,"There is no TypeDefinition defined");
			return false;
		}

		if(type->deployUnit.size() == 0)
		{
			LOGGER_WRITE(Logger::ERROR,"There is no DeployUnit defined");
			return false;
		}

		du =select_du_architecture(type);

		// check if exist
		map<string, void*>::const_iterator it = deploysUnits.find(du->internalGetKey());
		if (it != deploysUnits.end())
		{
			LOGGER_WRITE(Logger::INFO,"The DeployUnit is already loaded");	
			return true;
		}

		string libpath=	bootstrap->resolveDeployUnit(du);
		if(!libpath.empty())
		{
			LOGGER_WRITE(Logger::DEBUG,"install_deploy_unit "+libpath);
			void *handler = soloader_load(libpath);
			if(handler == NULL)
			{
				LOGGER_WRITE(Logger::ERROR,"failed install_deploy_unit "+libpath);
				return false;
			}
			LOGGER_WRITE(Logger::DEBUG,"done "+libpath);
			deploysUnits[du->internalGetKey()] = handler;
			return true;	
		}else
		{
			LOGGER_WRITE(Logger::ERROR,"The DeployUnit cannot be registred beacause the Typedefintion is not found "+libpath);	
			return false;	
		}		
	}
	catch ( const std::exception & e )
	{
		std::cerr << e.what() << endl;
		LOGGER_WRITE(Logger::ERROR,"");
		return false;
	}

}

AbstractTypeDefinition* DynamicLoader::create_instance(Instance *i)
{
	try
	{
		TypeDefinition *type = i->typeDefinition;
		if(type == NULL)
		{
			LOGGER_WRITE(Logger::ERROR,"There is no TypeDefinition define");
			return NULL;
		}

		DeployUnit *du  =select_du_architecture(type);

		// todo check if for me
		map<string, void*>::const_iterator it = deploysUnits.find(du->internalGetKey());
		if (it == deploysUnits.end())
		{
			LOGGER_WRITE(Logger::ERROR,"The DU is no registred");
			return NULL;
		}
		LOGGER_WRITE(Logger::DEBUG,"newInstance of "+du->name +" "+i->path());
		void *instance = newInstance(it->second);
		if(instance == NULL)
		{
			LOGGER_WRITE(Logger::ERROR,"Error during create Instance of "+du->name);
			return NULL;
		}
		instances[i->path()] = instance;
		return(AbstractTypeDefinition*)instance;
	}
	catch ( const std::exception & e )
	{
		std::cerr << e.what() << endl;
		return NULL;
	}

}





bool DynamicLoader::update_param(Instance *i,AbstractTypeDefinition *inst)
{

	TypeDefinition *type = 	i->typeDefinition;
	if(type != NULL && dynamic_cast<TypeDefinition*>(type) != 0)
	{
		DictionaryType *dtype = type->dictionaryType;
		if(dtype != NULL && dynamic_cast<DictionaryType*>(dtype) != 0)
		{
			Dictionary * dico =i->dictionary;
			for (std::map<string,DictionaryAttribute*>::const_iterator it = dtype->attributes.begin();  it != dtype->attributes.end(); ++it)
			{
				DictionaryAttribute *da = it->second;

				//fragmentDictionary
				if(dico != NULL && dico->values[da->name] != NULL)
				{
					inst->params[da->name] = dico->values[da->name]->value;
				}
				else if(i->fragmentDictionary[mservice->getNodeName()] != NULL && i->fragmentDictionary[mservice->getNodeName()]->values[da->name] != NULL )
				{

					LOGGER_WRITE(Logger::DEBUG,"fragmentDictionary "+ i->fragmentDictionary[mservice->getNodeName()]->values[da->name]->value);
					inst->params[da->name] = i->fragmentDictionary[mservice->getNodeName()]->values[da->name]->value;
				}
				else
				{
					cout << da->name << " defaultValue " << da->defaultValue << endl;
					inst->params[da->name] = 	da->defaultValue;
				}

			}
		}
	}
}


bool DynamicLoader::update_instance(Instance *i){

	AbstractTypeDefinition *inst = (AbstractTypeDefinition*)instances.find(i->path())->second;
	if(inst != NULL && dynamic_cast<AbstractTypeDefinition*>(inst) != 0)
	{
		LOGGER_WRITE(Logger::DEBUG,"invoke update "+i->name);
		try
		{
			update_param(i,inst);
			inst->update();
		}
		catch ( const std::exception & e )
		{
			std::cerr << e.what() << endl;
			return false;
		}
		return true;
	}
	return false;

}

bool DynamicLoader::start_instance(Instance *i)
{

	AbstractTypeDefinition *inst = (AbstractTypeDefinition*)instances.find(i->path())->second;
	if(inst != NULL && dynamic_cast<AbstractTypeDefinition*>(inst) != 0)
	{
		LOGGER_WRITE(Logger::DEBUG,"invoke start "+i->name);
		try
		{
			update_param(i,inst);
			inst->start();
		}
		catch ( const std::exception & e )
		{
			std::cerr << e.what() << endl;
			return false;
		}

		return true;
	}
	return false;

}


bool DynamicLoader::stop_instance(Instance *i)
{
	AbstractTypeDefinition *inst = (AbstractTypeDefinition*)instances.find(i->path())->second;
	if(inst != NULL && dynamic_cast<AbstractTypeDefinition*>(inst) != 0)
	{
		LOGGER_WRITE(Logger::DEBUG,"Invoke stop "+i->name);
		if(instances.find(i->path()) != instances.end()){
			inst->stop();
		}else {
			LOGGER_WRITE(Logger::WARNING,"Invoke stop but instance is not started "+i->name);
		}
		return true;
	}
	return false;
}


bool DynamicLoader::destroy_instance(Instance *i)
{
	TypeDefinition *type = i->typeDefinition;
	if(type == NULL)
	{
		LOGGER_WRITE(Logger::ERROR,"There is no TypeDefinition define");
		return false;
	}


	if(instances.find(i->path()) != instances.end())
	{

		AbstractTypeDefinition *inst = (AbstractTypeDefinition*)instances.find(i->path())->second;

		if(inst != NULL && dynamic_cast<AbstractTypeDefinition*>(inst) != 0)
		{





			DeployUnit *du  = select_du_architecture(type);
			LOGGER_WRITE(Logger::DEBUG,"Destroying deployunit "+du->name);
			// todo check if for me
			map<string, void*>::const_iterator it = deploysUnits.find(du->internalGetKey());
			if (it == deploysUnits.end())
			{
				LOGGER_WRITE(Logger::ERROR,"destroy instance but can't find deploy unit of STOP done");
				return false;
			}

			destroyInstance(it->second,inst);

			LOGGER_WRITE(Logger::DEBUG,"Cleaning instance cache "+i->path());
			instances.erase(instances.find(i->path()));






			// class 
			if(dlclose(it->second) != 0)
			{
				LOGGER_WRITE(Logger::WARNING,"dlclose");
			}else {

				deploysUnits.erase(deploysUnits.find(du->internalGetKey()));
			}



		}else 
		{
			LOGGER_WRITE(Logger::ERROR,"instance cannt be cast");
			return false;	
		}


	}

	return true;
}

#ifdef __MACH__
// TODO
#else
bool is_ELF(Elf32_Ehdr eh)
{
	/* ELF magic bytes are 0x7f,'E','L','F'
	 * Using  octal escape sequence to represent 0x7f
	 */
	if(!strncmp((char*)eh.e_ident, "\177ELF", 4)) {
		LOGGER_WRITE(Logger::DEBUG,"ELFMAGIC \t ELF");
		/* IS a ELF file */
		return 1;
	} else {
		LOGGER_WRITE(Logger::DEBUG,"ELFMAGIC mismatch!");
		/* Not ELF file */
		return 0;
	}
}
int DynamicLoader::read_elf_header(const char *elf_file){

	int32_t fd;
	Elf32_Ehdr eh;		/* elf-header is fixed size */
	Elf32_Shdr* sh_tbl;	/* section-header table is variable size */

	fd = open(elf_file, O_RDONLY|O_SYNC);

	assert(lseek(fd, (off_t)0, SEEK_SET) == (off_t)0);
	assert(read(fd, (void *)&eh, sizeof(Elf32_Ehdr)) == sizeof(Elf32_Ehdr));

	if(!is_ELF(eh)) {
		return 0;
	}
	if(fd<0) {
		LOGGER_WRITE(Logger::ERROR,"Error Unable to open file");
		return 0;
	}
	print_elf_header(eh);

	close(fd);
}


void DynamicLoader::print_elf_header(Elf32_Ehdr elf_header)
{

	/* Storage capacity class */
	LOGGER_WRITE(Logger::DEBUG,"Storage class");
	switch(elf_header.e_ident[EI_CLASS])
	{
	case ELFCLASS32:
		LOGGER_WRITE(Logger::DEBUG,"32-bit objects");
		break;

	case ELFCLASS64:
		LOGGER_WRITE(Logger::DEBUG,"64-bit objects");
		break;

	default:
		LOGGER_WRITE(Logger::DEBUG,"INVALID CLASS");
		break;
	}

	/* Data Format */
	LOGGER_WRITE(Logger::DEBUG,"Data format\t= ");
	switch(elf_header.e_ident[EI_DATA])
	{
	case ELFDATA2LSB:
		LOGGER_WRITE(Logger::DEBUG,"2's complement, little endian");
		break;

	case ELFDATA2MSB:
		LOGGER_WRITE(Logger::DEBUG,"2's complement, big endian");
		break;

	default:
		LOGGER_WRITE(Logger::DEBUG,"INVALID Format");
		break;
	}

	/* OS ABI */
	LOGGER_WRITE(Logger::DEBUG,"OS ABI\t\t= ");
	switch(elf_header.e_ident[EI_OSABI])
	{
	case ELFOSABI_SYSV:
		LOGGER_WRITE(Logger::DEBUG,"UNIX System V ABI");
		break;

	case ELFOSABI_HPUX:
		LOGGER_WRITE(Logger::DEBUG,"HP-UX");
		break;

	case ELFOSABI_NETBSD:
		LOGGER_WRITE(Logger::DEBUG,"NetBSD");
		break;

	case ELFOSABI_LINUX:
		LOGGER_WRITE(Logger::DEBUG,"Linux");
		break;

	case ELFOSABI_SOLARIS:
		LOGGER_WRITE(Logger::DEBUG,"Sun Solaris");
		break;

	case ELFOSABI_AIX:
		LOGGER_WRITE(Logger::DEBUG,"IBM AIX");
		break;

	case ELFOSABI_IRIX:
		LOGGER_WRITE(Logger::DEBUG,"SGI Irix");
		break;

	case ELFOSABI_FREEBSD:
		LOGGER_WRITE(Logger::DEBUG,"FreeBSD");
		break;

	case ELFOSABI_TRU64:
		LOGGER_WRITE(Logger::DEBUG,"Compaq TRU64 UNIX");
		break;

	case ELFOSABI_MODESTO:
		LOGGER_WRITE(Logger::DEBUG,"Novell Modesto");
		break;

	case ELFOSABI_OPENBSD:
		LOGGER_WRITE(Logger::DEBUG,"OpenBSD");
		break;

	case ELFOSABI_ARM_AEABI:
		LOGGER_WRITE(Logger::DEBUG,"ARM EABI");
		break;

	case ELFOSABI_ARM:
		LOGGER_WRITE(Logger::DEBUG,"ARM");
		break;

	case ELFOSABI_STANDALONE:
		LOGGER_WRITE(Logger::DEBUG,"Standalone (embedded) app");
		break;

	default:
		LOGGER_WRITE(Logger::DEBUG,"Unknown"); // (0x%x)\n", elf_header.e_ident[EI_OSABI]);
		break;
	}

	/* ELF filetype */
	LOGGER_WRITE(Logger::DEBUG,"Filetype \t= ");
	switch(elf_header.e_type)
	{
	case ET_NONE:
		LOGGER_WRITE(Logger::DEBUG,"N/A (0x0)");
		break;

	case ET_REL:
		LOGGER_WRITE(Logger::DEBUG,"Relocatable");
		break;

	case ET_EXEC:
		LOGGER_WRITE(Logger::DEBUG,"Executable");
		break;

	case ET_DYN:
		LOGGER_WRITE(Logger::DEBUG,"Shared Object");
		break;
	default:
		LOGGER_WRITE(Logger::DEBUG,"Unknown "); //(0x%x)\n", elf_header.e_type);
		break;
	}

	/* ELF Machine-id */
	LOGGER_WRITE(Logger::DEBUG,"Machine\t\t= ");
	switch(elf_header.e_machine)
	{
	case EM_NONE:
		LOGGER_WRITE(Logger::DEBUG,"None (0x0)");
		break;

	case EM_386:
		LOGGER_WRITE(Logger::DEBUG,"INTEL x86"); //(0x%x)\n", EM_386);
		break;

	case EM_ARM:
		LOGGER_WRITE(Logger::DEBUG,"ARM "); //(0x%x)\n", EM_ARM);
		break;
	case 0x3e:
		LOGGER_WRITE(Logger::DEBUG,"x86_64 ");
		break;

	default:

		printf("Machine\t=  0x%x\n", elf_header.e_machine);
		break;
	}

	/* Entry point
	printf("Entry point\t= 0x%08x\n", elf_header.e_entry);


	printf("ELF header size\t= 0x%08x\n", elf_header.e_ehsize);

// Program Header
	printf("\nProgram Header\t= ");
	printf("0x%08x\n", elf_header.e_phoff);		/ start
	printf("\t\t  %d entries\n", elf_header.e_phnum);	 num entry
	printf("\t\t  %d bytes\n", elf_header.e_phentsize);	 size/entry

	/// Section header starts at
	printf("\nSection Header\t= ");
	printf("0x%08x\n", elf_header.e_shoff);
	printf("\t\t  %d entries\n", elf_header.e_shnum);
	printf("\t\t  %d bytes\n", elf_header.e_shentsize);
	printf("\t\t  0x%08x (string table offset)\n", elf_header.e_shstrndx);

	/// File flags (Machine specific)
	printf("\nFile flags \t= 0x%08x\n", elf_header.e_flags);

	// ELF file flags are machine specific.
	 // INTEL implements NO flags.
	 // ARM implements a few.
	 //Add support below to parse ELF file flags on ARM

	int32_t ef = elf_header.e_flags;
	printf("\t\t  ");

	if(ef & EF_ARM_RELEXEC)
		printf(",RELEXEC ");

	if(ef & EF_ARM_HASENTRY)
		printf(",HASENTRY ");

	if(ef & EF_ARM_INTERWORK)
		printf(",INTERWORK ");

	if(ef & EF_ARM_APCS_26)
		printf(",APCS_26 ");

	if(ef & EF_ARM_APCS_FLOAT)
		printf(",APCS_FLOAT ");

	if(ef & EF_ARM_PIC)
		printf(",PIC ");

	if(ef & EF_ARM_ALIGN8)
		printf(",ALIGN8 ");

	if(ef & EF_ARM_NEW_ABI)
		printf(",NEW_ABI ");

	if(ef & EF_ARM_OLD_ABI)
		printf(",OLD_ABI ");

	if(ef & EF_ARM_SOFT_FLOAT)
		printf(",SOFT_FLOAT ");

	if(ef & EF_ARM_VFP_FLOAT)
		printf(",VFP_FLOAT ");

	if(ef & EF_ARM_MAVERICK_FLOAT)
		printf(",MAVERICK_FLOAT ");

	printf("\n");

	// MSB of flags conatins ARM EABI version
	printf("ARM EABI\t= Version %d\n", (ef & EF_ARM_EABIMASK)>>24);

	printf("\n");	End of ELF header */

}

#endif
void * DynamicLoader::soloader_load(std::string libpath)
{

	void* handle = dlopen(libpath.c_str(),RTLD_LAZY|RTLD_GLOBAL);

#ifdef __MACH__
	// TODO
#else
	read_elf_header(libpath.c_str());
#endif
	if (!handle)
	{

		LOGGER_WRITE(Logger::ERROR,"dlopen =>"+string(dlerror()));
		return NULL;
	}
	return handle;
}

void DynamicLoader::destroyInstance(void *handler,AbstractTypeDefinition *instance)
{
	LOGGER_WRITE(Logger::DEBUG,"DynamicLoader destroyInstance");
	// destructor
	void (*destroy)(AbstractTypeDefinition*);
	destroy = (void (*)(AbstractTypeDefinition*))dlsym(handler, "destroy_object");
	destroy(instance);
}

AbstractTypeDefinition * DynamicLoader::newInstance(void *handle)
{
	LOGGER_WRITE(Logger::DEBUG,"DynamicLoader Instance");
	AbstractTypeDefinition* (*create)();
	create =  (AbstractTypeDefinition* (*)())dlsym(handle, "create");
	if(!create){
		LOGGER_WRITE(Logger::ERROR,"cannot find symbol newInstance");
		return NULL;
	}
	AbstractTypeDefinition* c = (AbstractTypeDefinition*)create();
	return c;
}


