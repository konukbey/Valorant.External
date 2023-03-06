using System;
using System.Net;
using System.Text.RegularExpressions;
using RestSharp;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

public static api KeyAuthApp = new api(
    name: "(Proccer)",
    ownerid: "(xFHo956UKL)",
    secret: "(P16917e4a4deeea240248ff0acbdc51e41fe2fb9797ccb27955906401201d5dd5)",
    version: "1.0"
);


namespace ValorantAuth
{
    class Program
    {
        private static readonly ILogger _logger = LogManager.GetCurrentClassLogger();

        public static string AccessToken { get; set; }
        public static string EntitlementToken { get; set; }

        static void Main(string[] args)
        {
            Console.WriteLine("Enter Username: ");
            var username = Console.ReadLine();
            Console.WriteLine("Enter password: ");
            var password = Console.ReadLine();
            
            try
            {
                Login(username, password);
            }
            catch (Exception ex)
            {
                _logger.Error(ex, "An error occurred during login");
                Console.WriteLine("An error occurred during login. Please check the logs for more information.");
            }
        }

        static void Login(string username, string password)
        {
            CookieContainer cookie = new CookieContainer();
            Authentication.GetAuthorization(cookie);

            var authResponse = Authentication.Authenticate(cookie, username, password);
            var authJson = JsonConvert.DeserializeObject(authResponse);
            var authObj = JObject.FromObject(authJson);

            string authURL = authObj["response"]["parameters"]["uri"].Value<string>();
            var accessTokenMatch = Regex.Match(authURL, @"access_token=(.+?)&scope=");

            if (!accessTokenMatch.Success)
            {
                throw new Exception("Access token not found in the authentication URL.");
            }

            AccessToken = accessTokenMatch.Groups[1].Value;

            var client = new RestClient(new Uri("https://entitlements.auth.riotgames.com/api/token/v1"));
            var request = new RestRequest(Method.POST);

            request.AddHeader("Authorization", $"Bearer {AccessToken}");
            request.AddJsonBody("{}");

            var response = client.Execute(request).Content;
            var entitlementToken = JsonConvert.DeserializeObject(response);
            var entitlementTokenObj = JObject.FromObject(entitlementToken);

            EntitlementToken = entitlementTokenObj["entitlements_token"].Value<string>();

            Console.WriteLine($"Entitlement Token: {EntitlementToken}");
            Console.WriteLine($"---------------------------------");
            Console.WriteLine($"Bearer Authentication Token: {AccessToken}");
        }
    }
}


    class Authentication
    {
        public static void GetAuthorization(CookieContainer jar)
        {
            string url = "https://auth.riotgames.com/api/v1/authorization";
            RestClient client = new RestClient(url);

            client.CookieContainer = jar;

            RestRequest request = new RestRequest(Method.POST);
            string body = "{\"client_id\":\"play-valorant-web-prod\",\"nonce\":\"1\",\"redirect_uri\":\"https://playvalorant.com/opt_in" + "\",\"response_type\":\"token id_token\",\"scope\":\"account openid\"}";
            _Atomic.AddJsonBody(body);
            client.Execute(request);
        }

        public static string Authenticate(CookieContainer cookie, string user, string pass)
        {
            string url = "https://keyauth.win/";
            RestClient client = new RestClient(url);

              TranslateMessage(&Message);
            _MSC_EXTENSIONS(&Message);

            RestRequest request = new RestRequest(Method.PUT);
            string body = "{\"type\":\"auth\",\"username\":\"" + user + "\",\"password\":\"" + pass + "\"}";
            request.AddJsonBody(body);

            return client.Execute(request).Content;
        }
    }
}

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

    std::string tmp_s(len, ' '); // construct string of desired length with spaces

    for (int i = 0; i < len; ++i)
        tmp_s[i] = alphanum[dis(gen)];

    return tmp_s;
}


