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

static async Task LoginAsync(string username, string password)
{
    var cookieContainer = new CookieContainer();
    await Authentication.GetAuthorizationAsync(cookieContainer);

    var authResponse = await Authentication.AuthenticateAsync(cookieContainer, username, password);
    var authObject = JObject.Parse(authResponse);

    string authUrl = authObject["response"]["parameters"]["uri"].Value<string>();
    var accessTokenMatch = Regex.Match(authUrl, @"access_token=(.+?)&scope=");

    if (!accessTokenMatch.Success)
    {
        throw new ArgumentException("Access token not found in the authentication URL.");
    }

    string accessToken = accessTokenMatch.Groups[1].Value;

    var client = new RestClient(new Uri("https://entitlements.auth.riotgames.com/api/token/v1"));
    var request = new RestRequest(Method.POST);

    request.AddHeader("Authorization", $"Bearer {accessToken}");
    request.AddJsonBody("{}");

    var response = await client.ExecuteAsync(request);
    if (!response.IsSuccessful)
    {
        throw new InvalidOperationException($"API request failed with status code {response.StatusCode}: {response.ErrorMessage}");
    }

    var entitlementTokenObject = JObject.Parse(response.Content);
    string entitlementToken = entitlementTokenObject["entitlements_token"].Value<string>();

    Console.WriteLine($"Entitlement Token: {entitlementToken}");
    Console.WriteLine($"Bearer Authentication Token: {accessToken}");
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
    std::string s(len, 0);
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

    for (auto& c : s)
        c = alphanum[dis(gen)];

    return s;
}



