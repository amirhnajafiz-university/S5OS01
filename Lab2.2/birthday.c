#include <linux/init.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/module.h>

static LIST_HEAD(birthday_list);

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

struct birthday *amir;
struct birthday *farshid;
struct birthday *mina;
struct birthday *shayan;
struct birthday *mohammad;

int simple_init(void)
{
	printk(KERN_INFO "Loading Module\n");
	
	amir = kmalloc(sizeof(*amir), GFP_KERNEL);
	amir->day = 17;
	amir->month = 1;
	amir->year = 2001;

	INIT_LIST_HEAD(&amir->list);

	farshid = kmalloc(sizeof(*farshid), GFP_KERNEL);
	farshid->day = 25;
	farshid->month = 6;
	farshid->year = 2000;
	
	INIT_LIST_HEAD(&farshid->list);

	mina = kmalloc(sizeof(*mina), GFP_KERNEL);
	mina->day = 7;
	mina->month = 12;
	mina->year = 2001;

	INIT_LIST_HEAD(&mina->list);

	shayan = kmalloc(sizeof(*shayan), GFP_KERNEL);
	shayan->day = 17;
	shayan->month = 7;
	shayan->year = 2000;

	INIT_LIST_HEAD(&shayan->list);

	mohammad = kmalloc(sizeof(*mohammad), GFP_KERNEL);
	mohammad->day = 28;
	mohammad->month = 1;
	mohammad->year = 2000;

	INIT_LIST_HEAD(&mohammad->list);
	
	list_add_tail(&amir->list, &birthday_list);
	list_add_tail(&farshid->list, &birthday_list);
	list_add_tail(&mina->list, &birthday_list);
	list_add_tail(&shayan->list, &birthday_list);
	list_add_tail(&mohammad->list, &birthday_list);
	
	struct birthday *ptr;
	list_for_each_entry(ptr, &birthday_list, list) {
		printk(KERN_INFO "%d%d%d \n", ptr->month, ptr->day, ptr->year);
	}

	return 0;
}

void simple_exit(void)
{
	printk(KERN_INFO "Removing Module\n");
	struct list_head *ptr, *next;
	list_for_each_safe(ptr, next, &amir->list) {
		list_del(ptr);
		kfree(ptr);
	}
	return 0;
}

module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple module");
MODULE_AUTHOR("SGG");
