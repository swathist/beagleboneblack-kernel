#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

#include <linux/mod_devicetable.h>
#include <linux/property.h>
#include <linux/platform_device.h>
#include <linux/of_device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Swathi ST");
MODULE_DESCRIPTION("Module to read Device Tree Information");

int var=12;
module_param(var,int,0644);

static int my_device_probe(struct platform_device *pdev);
static int my_device_remove(struct platform_device *pdev);

static struct of_device_id my_driver_ids[] = {
	{
		.compatible = "SDE1",
		.name = "biodata",
	}, {},
};
MODULE_DEVICE_TABLE(of, my_driver_ids);

static struct platform_driver my_driver = {
	.probe = my_device_probe,
	.remove = my_device_remove,
	.driver = {
		.name = "my_device",
		.of_match_table = my_driver_ids,
	},
};

static int my_device_probe(struct platform_device *pdev) 
{
	struct device *dev = &pdev->dev;
        const char *myname;
        int myid, ret;

        printk("dt_probe - Now I am in the probe function!\n");

        /* Check for device properties */
        if(!device_property_present(dev, "myname")) {
                printk("dt_probe - Error! Device property 'myname' not found!\n");
                return -1;
        }
        if(!device_property_present(dev, "myid")) {
                printk("dt_probe - Error! Device property 'myid' not found!\n");
                return -1;
        }

        /* Read device properties */
        ret = device_property_read_string(dev, "myname", &myname);
        if(ret) {
                printk("dt_probe - Error! Could not read 'myname'\n");
                return -1;
        }
        printk("dt_probe - myname: %s\n", myname);
        
	ret = device_property_read_u32(dev, "myid", &myid);
        if(ret) {
                printk("dt_probe - Error! Could not read 'myid'\n");
                return -1;
        }
        printk("dt_probe - myid: %d\n", myid);

        return 0;
}

static int my_device_remove(struct platform_device *pdev) 
{
	printk("dt_probe - Now I am in the remove function\n");
        return 0;
}

static int hello_init(void)
{
	platform_driver_register(&my_driver);
	printk("Init function var:%d\n",var);
	return 0;
}

static void hello_exit(void)
{
	platform_driver_unregister(&my_driver);
	printk("Exit function\n");
}

module_init(hello_init);
module_exit(hello_exit);
