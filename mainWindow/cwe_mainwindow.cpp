#include "cwe_mainwindow.h"
#include "ui_cwe_mainwindow.h"

#include <QDebug>

CWE_MainWindow::CWE_MainWindow(VWTinterfaceDriver *newDriver, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CWE_MainWindow)
{
    ui->setupUi(this);

    myDriver = newDriver;
    dataLink = myDriver->getDataConnection();

    /* add the sidebar */
    QWidget *frameSideBar = this->findChild<QWidget *>("SideBar");
    taskSideBar = new SideBar(frameSideBar);
    QGridLayout *layout = new QGridLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(taskSideBar);
    frameSideBar->setLayout(layout);

    /* populate the stacked widget */

    // get the stacked widget container
    widgetStack = this->findChild<QWidget *>("stackContainer");

    stackLayout = new QStackedLayout();
    stackLayout->setContentsMargins(0,0,0,0);

    // 1) create new simulation
    taskLanding          = new CWE_landing(widgetStack);
    stackedWidgetsIndex.insert(TASK_LANDING, stackLayout->addWidget(taskLanding));

    taskCreateSimulation = new CWE_create_simulation(widgetStack);
    stackedWidgetsIndex.insert(TASK_CREATE_NEW_SIMULATION, stackLayout->addWidget(taskCreateSimulation));

    // 2) manage and run simulation
    taskManageSimulation = new CWE_manage_simulation(widgetStack);
    stackedWidgetsIndex.insert(TASK_MANAGE_SIMULATION, stackLayout->addWidget(taskManageSimulation));

    // 3) manage and download remote files
    taskFileManager      = new CWE_file_manager(widgetStack);
    stackedWidgetsIndex.insert(TASK_MANAGE_FILES, stackLayout->addWidget(taskFileManager));

    // 4) manage remote job
    taskSimulationDetail = new CWE_simulation_details(widgetStack);
    stackedWidgetsIndex.insert(TASK_SIMULATION_DETAILS, stackLayout->addWidget(taskSimulationDetail));

    taskTaskList         = new CWE_task_list(widgetStack);
    stackedWidgetsIndex.insert(TASK_LIST_TASKS, stackLayout->addWidget(taskTaskList));

    // 5) tutorial and help
    taskHelp             = new CWE_help(widgetStack);
    stackedWidgetsIndex.insert(TASK_HELP, stackLayout->addWidget(taskHelp));

    widgetStack->setLayout(stackLayout);

    task_selected(TASK_LANDING);

    connect(taskSideBar, SIGNAL(taskSelected(TASK)), this, SLOT(task_selected(TASK)));
    connect(taskManageSimulation, SIGNAL(CWE_manage_simulation_signal(TASK)), this, SLOT(task_selected(TASK)));
    connect(taskCreateSimulation, SIGNAL(CWE_create_simulation_signal(TASK, SIM_MODE)), this, SLOT(create_simulation_task_selected(TASK, SIM_MODE)));
}

void CWE_MainWindow::runSetupSteps()
{
    taskTaskList->linkJobHandle(myDriver->getJobHandler());
}

CWE_MainWindow::~CWE_MainWindow()
{
    delete ui;
    if (taskCreateSimulation) delete taskCreateSimulation;
    if (taskFileManager) delete taskFileManager;
    if (taskLanding) delete taskLanding;
    if (taskManageSimulation) delete taskManageSimulation;
    if (taskSimulationDetail) delete taskSimulationDetail;
    if (taskTaskList) delete taskTaskList;
    if (taskHelp) delete taskHelp;
}

void CWE_MainWindow::menuCopyInfo()
{
    CopyrightDialog copyrightPopup;
    copyrightPopup.exec();
}

void CWE_MainWindow::menuExit()
{
    myDriver->shutdown();
}

void CWE_MainWindow::on_action_Quit_triggered()
{
    myDriver->shutdown();
}

/* side bar functionality */
void CWE_MainWindow::task_selected(TASK task)
{
    stackLayout->setCurrentIndex(stackedWidgetsIndex.value(task));
}

void CWE_MainWindow::create_simulation_task_selected(TASK task, SIM_MODE mode)
{
    /* mode is SIM_MODE_2D or SIM_MODE_3D, depending on which putton was clicked */
    task_selected(task);
}

void CWE_MainWindow::selectLanding()
{
}

void CWE_MainWindow::selectCreateSimulation()
{
}

void CWE_MainWindow::selectManageRun()
{
}

void CWE_MainWindow::selectManageJobs()
{
}

void CWE_MainWindow::selectManageFiles()
{
}

void CWE_MainWindow::selectHelp()
{
}


void CWE_MainWindow::on_actionOpen_triggered()
{

}

void CWE_MainWindow::on_actionOpen_existing_triggered()
{

}

void CWE_MainWindow::on_actionSave_triggered()
{

}

void CWE_MainWindow::on_actionSave_As_triggered()
{

}

void CWE_MainWindow::on_actionAbout_CWE_triggered()
{

}


void CWE_MainWindow::on_actionCreate_New_Simulation_triggered()
{
    task_selected(TASK_CREATE_NEW_SIMULATION);
}

void CWE_MainWindow::on_actionManage_Simulation_triggered()
{
    task_selected(TASK_MANAGE_SIMULATION);
}

void CWE_MainWindow::on_actionHelp_triggered()
{
    task_selected(TASK_HELP);
}

void CWE_MainWindow::on_action_Landing_Page_triggered()
{
    task_selected(TASK_LANDING);
}

void CWE_MainWindow::on_actionManage_Remote_Jobs_triggered()
{
    task_selected(TASK_LIST_TASKS);
}

void CWE_MainWindow::on_actionTutorials_and_Help_triggered()
{
    task_selected(TASK_HELP);
}

void CWE_MainWindow::on_actionManage_and_Download_Files_triggered()
{
    task_selected(TASK_MANAGE_FILES);
}
