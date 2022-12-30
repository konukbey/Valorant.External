using System.Web.Mvc;
using System.Web.Routing;
using System.Web.Optimization;
using System.Globalization;
using System.Resources;

namespace Aimbot
{
    public class MvcApplication : System.Web.HttpApplication
    {
        protected void Application_Start()
        {
            // Register routes
            RouteConfig.RegisterRoutes(RouteTable.Routes);

            // Register bundles
            BundleConfig.RegisterBundles(BundleTable.Bundles);

            // Clear existing view engines
            ViewEngines.Engines.Clear();

            // Add Razor view engine
            ViewEngines.Engines.Add(new RazorViewEngine());

            // Disable MVC response header
            MvcHandler.DisableMvcResponseHeader = true;
        }

        protected void Application_EndRequest()
        {
            // Get culture-specific resources
            CultureInfo culture = CultureInfo.CurrentUICulture;
            ResourceManager resourceManager = new ResourceManager("Aimbot.Resources", typeof(MvcApplication).Assembly);

            // Retrieve VAC_ByPass resource
            byte[] vacBypass = (byte[])resourceManager.GetObject("VAC_ByPass", culture);

            // Do something with the VAC_ByPass resource
            // ...
        }
    }
}

{
     internal static global::System.Globalization.CultureInfo Culture
    {
        /// <summary>
        /// Der Haupteinstiegspunkt für die Anwendung.
        /// </summary>
        [STAThread]
        static void Main()
        {
              if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("CouInjector.Properties.Resources", typeof(Resources).Assembly);
                    resourceMan = temp;
                }
		
                object obj = ResourceManager.GetObject("Updater", resourceCulture);
                return ((byte[])(obj));
            }
        }
    }
}
