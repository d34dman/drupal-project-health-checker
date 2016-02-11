I. INSTALLATION
  1. Using multibasebox
    1. Checkout the repo and run following commands.
      >>fab config:mbb docker:run
      >>fab config:mbb install
      >>fab config:mbb reset
  2. Manual
    1. Install Drupal which can be found in public folder in the root of the repo.
    2. Enable dcasia16projecthealth_deploy module.
    3. Set up cron job to run every 5 minutes.

II. USAGE
  1. Log in to Drupal as admin
  2. Use the "plus" sign on the left side bar to bring up a form to add a project
     snapshot.
  3. Use machine name of a valid project from Drupal.org
  4. Once you submit the form, it will redirect to a page where it will display
     the progress of indexing. Once indexing is complete, this page will display
     various metrics regarding project health.

III. NOTE:
  Indexing of snapshot is done on cron runs. so make sure you configure cron jobs
  properly.
  Time required to index depends on the data available for the projects. So if you
  try to index a project which has very few issues and comments, it will be faster.


IV. CREDITS
  1 CMS:
    1. Drupal
  2 Theme:
    1. Bootstrap Theme
    1. AdminLTE Dashboard Theme
  3 LIBRARIES:
    1. jquery & jquery UI
    2. d3js
